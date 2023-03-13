#pragma once
#include <cstdint>

/// <summary>
/// ECSDefinitions stores common typedefs/data for the ECS system.
/// </summary>
const uint64_t MAX_ENTITIES = 20000;
const size_t MAX_COMPONENTS = 64;

typedef uint32_t EntityIndex;
typedef uint32_t EntityVersion;
typedef uint64_t EntityID;
typedef size_t ComponentID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;