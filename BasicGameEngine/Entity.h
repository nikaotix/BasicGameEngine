#pragma once

#include <cstdint>
#include <bitset>
#include "ECSDefinitions.h"

typedef struct {
	EntityID id;
	ComponentMask components;
} Entity;

// store index in top half, version in bottom half
inline EntityID CreateEntityId(EntityIndex index, EntityVersion version)
{
	return ((EntityID)index << 32) | ((EntityID)version);
}

inline EntityIndex GetEntityIndex(EntityID id)
{
	return id >> 32;
}

inline EntityVersion GetEntityVersion(EntityID id)
{
	return (EntityVersion)id;
}

inline bool IsEntityValid(EntityID id)
{
	// Check if the index is our invalid index
	return (id >> 32) != EntityIndex(-1);
}

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)