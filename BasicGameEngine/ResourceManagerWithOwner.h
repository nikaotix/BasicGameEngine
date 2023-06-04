#pragma once
#include "ResourceManager.h"

/// <summary>
/// Adds an Owner member to the ResourceManager,
/// to be used when loading resources that need
/// some external state to be loaded.
/// </summary>
template <typename ID, typename Resource, typename Owner>
class ResourceManagerWithOwner : public ResourceManager<ID, Resource>
{
private:
	Owner* owner{};
public:

	void Init(Owner* pOwner)
	{
		owner = pOwner;
	}

	virtual void Load(ID id)
	{
		std::shared_lock<std::shared_mutex> lock(this->mtx);
		Resource* pRsrc = new Resource(id, owner);
		this->rsrcMap[id] = {pRsrc, 0};
	}
};