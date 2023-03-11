#pragma once

#include <vector>
#include "Entity.h"
#include "ComponentID.h"
#include "ComponentPool.h"
class Scene
{
public:
	std::vector<Entity> entities;
	std::vector<ComponentPool> componentPools;

	// create a new entity
	EntityID NewEntity();

	// create component and assign to entity
	template <typename T>
	T* Assign(EntityID id);



};
