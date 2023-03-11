#include "Scene.h"

EntityID Scene::NewEntity()
{
    entities.push_back({ entities.size(), ComponentMask() });
    return entities.back().id;
}

template<typename T>
T* Scene::Assign(EntityID id)
{
    int componentId = GetID<T>();

    if (componentPools.size() <= componentId) // expand the component pool vector if needed
    {
        componentPools.resize(componentId + 1, nullptr);
    }
    if (componentPools[componentId] == nullptr) // create component pool if needed
    {
        componenetPools[componentId] = new ComponentPool(sizeof(T));
    }

    // create the new component at the entity ID location in the proper pool.
    T* pComponent = new (componentPools[componentId]->get(GetEntityIndex(id))) T();

    // set component bit in the entity and return the component
    entities[id].mask.set(componentId);
    return pComponent;
}