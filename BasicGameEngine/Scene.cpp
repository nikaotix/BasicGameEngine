#include "Scene.h"

EntityID Scene::NewEntity()
{
    if (!freeEntities.empty()) {
        EntityIndex newIndex = freeEntities.back();
        freeEntities.pop_back();
        EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id)); //restore the ID with the new version from the delete
        entities[newIndex].id = newID;
        return entities[newIndex].id;
    }
    entities.push_back({ entities.size(), ComponentMask() });
    return entities.back().id;
}

void Scene::DeleteEntity(EntityID id)
{
    EntityIndex index = GetEntityIndex(id);
    EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1); //create invalid entity index and update version
    entities[index].id = newID; //update that entity ID with the invalid entry
    entities[index].components.reset(); //clear all components
    freeEntities.push_back(index); //mark index as free
}

template<typename T>
T* Scene::Assign(EntityID id)
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

template<typename T>
void Scene::Remove(EntityID id)
{
    if (!EntityIsCurrent(id))
    {
        return;
    }

    int componentId = GetID<T>();
    entities[GetEntityIndex(id)].components.reset(componentId);

}

template<typename T>
T* Scene::Get(EntityID id)
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
