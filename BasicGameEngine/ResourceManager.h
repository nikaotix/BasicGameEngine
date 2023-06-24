#pragma once

#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <utility>
#include <functional>
/// <summary>
/// Simple-ish class to handle loading/unloading of data resources.
/// ID is a unique identifier, Resource is the object/struct that we're
/// managing access to, and Owner is something that has
/// internal resources used to create/destroy the Resource.
/// Resource types must support constructor with ID + owner, and free.
/// </summary>
template <typename ID, typename Resource>
class ResourceManager
{
public:
	struct CountedResource
	{
		Resource* rsrc;
		size_t count;
	};
	struct LockedResource
	{
		Resource* rsrc;
		std::shared_lock<std::shared_mutex> lock;
	};
protected:
	std::unordered_map<ID, CountedResource> rsrcMap;
	std::shared_mutex mtx;

private:
	// private free fuction to share between public Free/Cleanup functions.
	// DON'T USE THIS WITHOUT A LOCK
	void _Free(ID id)
	{
		if (rsrcMap.find(id) == rsrcMap.end())
		{
			return false;
		}
		if (rsrcMap[id].count != 0)
		{
			return false;
		}
		free(rsrcMap[id].rsrc);
		rsrcMap.erase(id);
	}

public:


	// This will invalidate a bunch of stuff, please be careful when doing this!
	// TODO: write this
	~ResourceManager()
	{
	}

	LockedResource Get(ID id)
	{
		std::shared_lock<std::shared_mutex> lock(mtx);

		return {rsrcMap[id].rsrc, std::move(lock)};
	}

	virtual void Load(ID id) = 0;

	bool Check(ID id)
	{
		return (rsrcMap.find(id) != rsrcMap.end());
	}

	bool Free(ID id)
	{
		std::unique_lock<std::shared_mutex> lock(mtx);
		_Free(id);
	}
	
	void Use(ID id)
	{
		std::unique_lock<std::shared_mutex> lock(mtx);
		if (rsrcMap.find(id) == rsrcMap.end())
		{
			return;
		}
		rsrcMap[id].count++;
	}
	void Release(ID id)
	{
		std::unique_lock<std::shared_mutex> lock(mtx);
		if (rsrcMap.find(id) == rsrcMap.end())
		{
			return;
		}
		if (rsrcMap[id].count == 0)
		{
#ifdef _DEBUG
			std::cout << "Trying to release unused resource?" << std::endl;
#endif
			return;
		}

		rsrcMap[id].count--;

	}

	void Cleanup()
	{
		std::unique_lock<std::shared_mutex> lock(mtx);
		std::vector<ID> toFree;

		for (auto rsrcIter = rsrcMap.cbegin(); rsrcIter != rsrcMap.cend(); ++rsrcIter)
		{
			if (rsrcIter->second.count <= 0)
			{
				toFree.push_back(rsrcIter->first);
			}
		}
		for (auto idIter = toFree.cbegin(); idIter != toFree.cend(); ++idIter)
		{
			_Free(*idIter);
		}
	}

};