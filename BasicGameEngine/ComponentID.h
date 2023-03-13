#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <utility>
/// <summary>
/// ComponentID stores the GetID function that generates
/// the component IDs at runtime.
/// </summary>

extern size_t s_componentCounter;

template <class T>
size_t GetID()
{
	static size_t s_componentID = s_componentCounter++;
	return s_componentID;
}
