#pragma once
#include "ResourceManager.h"

/// <summary>
/// Implements Load without an Owner,
/// trying to fix weird inheritance issue? idk
/// </summary>
template <typename ID, typename Resource>
class ResourceManagerWithoutOwner : public ResourceManager<ID, Resource>
{
public:

	virtual void Load(ID id)
	{
		std::shared_lock<std::shared_mutex> lock(this->mtx);
		Resource* pRsrc = new Resource(id);
		this->rsrcMap[id] = {pRsrc, 0};
	}
};