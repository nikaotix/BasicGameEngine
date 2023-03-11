#pragma once

#include <vector>
#include "Entity.h"
#include "ComponentID.h"
#include "ComponentPool.h"
#include "Transform.h"
#include "Velocity.h"
#include "Name.h"

class Scene
{
public:

	// create a new entity
	EntityID NewEntity();

	// delete an entity
	void DeleteEntity(EntityID id);

	inline bool EntityIsCurrent(EntityID id)
	{
		return (entities[GetEntityIndex(id)].id == id);
	}

	// create component and assign to entity
	template<typename T>
	T* Assign(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{
			return nullptr;
		}

		int componentId = GetID<T>();

		if (componentPools.size() <= componentId) // expand the component pool vector if needed
		{
			componentPools.resize(componentId + 1, nullptr);
		}
		if (componentPools[componentId] == nullptr) // create component pool if needed
		{
			componentPools[componentId] = new ComponentPool(sizeof(T));
		}

		// create the new component at the entity ID location in the proper pool.
		T* pComponent = new (componentPools[componentId]->get(GetEntityIndex(id))) T();

		// set component bit in the entity and return the component
		entities[id].components.set(componentId);
		return pComponent;
	}
	// remove component from entity bitmask (don't need to clear the data)
	template<typename T>
	void Remove(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{
			return;
		}

		int componentId = GetID<T>();
		entities[GetEntityIndex(id)].components.reset(componentId);

	}

	// get the component of type T owned by entity id.
	template<typename T>
	T* Get(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{

		}

		uint32_t componentId = GetID<T>();
		if (!entities[id].components.test(componentId))
		{
			return nullptr;
		}
		T* pComponent = static_cast<T*>(componentPools[componentId]->get(id));
		return pComponent;
	}


	//TODO: limit access to these somehow
	std::vector<Entity> entities;
	std::vector<EntityIndex> freeEntities;
	std::vector<ComponentPool*> componentPools;
};

template <typename... ComponentTypes>
class SceneView
{
	public:
	
	SceneView(Scene& scene) : pScene(&scene)
	{
		if (sizeof...(ComponentTypes) == 0)
		{
			all = true;
		}
		else
		{
			int componentIds[] = { 0, GetID<ComponentTypes>()... };
			for (size_t i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
			{
				componentMask.set(componentIds[i]);
			}
		}
	}

	class Iterator
	{
	private:
		inline bool ValidIndex()
		{
			// check if the index is valid and contains all the components we want
			return IsEntityValid(pScene->entities[index].id) &&
				(all || (mask == (mask & pScene->entities[index].components)));
		}

	public:
		Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
			: pScene(pScene), index(index), mask(mask), all(all) {}

		EntityID operator*() const
		{
			// give back the entityID we're currently at
			return pScene->entities[index].id;
		}

		bool operator==(const Iterator& other) const
		{
			// Compare two iterators
			return (index == other.index) || (index == pScene->entities.size());
		}

		bool operator!=(const Iterator& other) const
		{
			// Similar to above
			return (index != other.index) && (index != pScene->entities.size());
		}

		Iterator& operator++()
		{
			// Move the iterator forward
			do
			{
				index++;
			} while (index < pScene->entities.size() && !ValidIndex());
			return *this;
		}
	private:
		EntityIndex index;
		Scene* pScene;
		ComponentMask mask;
		bool all{ false };
	};

	const Iterator begin() const
	{
		// Give an iterator to the beginning of this view
		int firstIndex = 0;
		while (firstIndex < pScene->entities.size() &&
			(componentMask != (componentMask & pScene->entities[firstIndex].components)
				|| !IsEntityValid(pScene->entities[firstIndex].id)))
		{
			firstIndex++;
		}
		return Iterator(pScene, firstIndex, componentMask, all);
	}

	// TODO maybe: support backwards iteration?
	const Iterator end() const
	{
		// Give an iterator to the end of this view 
		return Iterator(pScene, EntityIndex(pScene->entities.size()), componentMask, all);
	}
		Scene* pScene{ nullptr };
		ComponentMask componentMask;
		bool all{ false };
};