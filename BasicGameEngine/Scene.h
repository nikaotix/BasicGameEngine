#pragma once

#include <vector>
#include <functional>
#include "Entity.h"
#include "ComponentID.h"
#include "ComponentPool.h"
#include "Components.h"


template <typename... ComponentTypes>
class SceneView;

/// <summary>
/// A Scene contains and manages all the entities and components
/// in this current game world. Probably entirely possible to have
/// multiple Scenes at once.
/// </summary>
class Scene
{

private:
	uint64_t sceneBeginPerfCounter;
	uint64_t currentStepBeginPerfCounter;
	uint64_t deltaPerfCounter;
public:

	const uint64_t getSceneBeginPerfCounter() { return sceneBeginPerfCounter; }
	const uint64_t getCurrentStepBeginPerfCounter() { return currentStepBeginPerfCounter; }
	const uint64_t getDeltaPerfCounter() { return deltaPerfCounter; }


	void Init(uint64_t sceneBeginPerfCounter)
	{
		sceneBeginPerfCounter = sceneBeginPerfCounter;
		currentStepBeginPerfCounter = sceneBeginPerfCounter;
		deltaPerfCounter = 0;
	}
	// create a new entity
	EntityID NewEntity();

	// delete an entity
	void DeleteEntity(EntityID id);

	inline bool EntityIsCurrent(EntityID id)
	{
		return (entities[GetEntityIndex(id)].id == id);
	}


	template <class T>
	void RegisterComponent(const std::string& name, std::vector<std::pair<std::string, std::function<void(EntityID)>>> vec)
	{
		ComponentID componentID = GetID<T>();
		if (vec.size() <= (componentID))
		{
			vec.resize(componentID + 1);
		}
		vec.emplace_back(std::make_pair(name, std::function<void(EntityID)>(Assign<T>)));
	};

	// create component and assign to entity
	template<typename T>
	void Assign(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{
			return;
		}

		ComponentID componentId = GetID<T>();

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

		// set component bit in the entity.
		entities[id].components.set(componentId);
	}

	// remove component from entity bitmask (don't need to clear the data)
	template<typename T>
	void Remove(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{
			return;
		}

		ComponentID componentId = GetID<T>();
		entities[GetEntityIndex(id)].components.reset(componentId);

	}

	// get the component of type T owned by entity id.
	template<typename T>
	T* Get(EntityID id)
	{
		if (!EntityIsCurrent(id))
		{
			return nullptr;
		}

		ComponentID componentId = GetID<T>();
		if (!entities[id].components.test(componentId))
		{
			return nullptr;
		}
		T* pComponent = static_cast<T*>(componentPools[componentId]->get(id));
		return pComponent;
	}

	// calls all systems registered to this scene in order.
	// TODO: add system groups (run multiple systems in parallel)
	// (probably just another vector of functions that get called as threads)
	void Update(uint64_t currentTimePerfCounter);


	//TODO: limit access to these somehow
	std::vector<Entity> entities;
	std::vector<EntityIndex> freeEntities;
	std::vector<ComponentPool*> componentPools;
	std::vector<std::function<void(Scene&)>> systems;
	std::vector<std::pair<std::string, std::function<void(EntityID)>>> assignFromComponentIDList;
};


/// <summary>
/// A SceneView provides an iterator that returns all entities with a
/// given set of components - used by various Systems to go through the
/// data quickly.
/// </summary>
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
			ComponentID componentIds[] = { 0, GetID<ComponentTypes>()... };
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