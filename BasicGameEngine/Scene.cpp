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

void Scene::Update()
{
    for (auto& func : systems)
    {
        func(*this);
    }
}
