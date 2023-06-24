#pragma once
#include <vector>
#include "Entity.h"

/// <summary>
/// The CollisionList is updated every frame for objects that care about what they collide with.
/// We never empty the list, just update the numCollisions so we ignore old collisions
/// that happen to be kept later in the list.
/// </summary>
typedef struct
{
	size_t numCollisions;
	std::vector<EntityID> collisions;
} CollisionList;