#pragma once
#include "ECSDefinitions.h"

class ComponentPool
{
public:
	ComponentPool(size_t componentSize)
	{
		componentSize = componentSize;
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
	size_t componentSize;
	char* pData {
		nullptr
	};
};

