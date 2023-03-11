#pragma once
#include "ECSDefinitions.h"

/// <summary>
/// ComponentPool manages the memory used by each component type.
/// </summary>
class ComponentPool
{
public:
	ComponentPool(size_t componentSize)
	{
		this->componentSize = componentSize;
		pData = new char[MAX_ENTITIES * componentSize];
	}
	~ComponentPool()
	{
		delete[] pData;
	}

	inline void* get(size_t index)
	{
		return pData + (index * componentSize);
	}


private:	
	size_t componentSize{ 0 };
	char* pData {
		nullptr
	};
};

