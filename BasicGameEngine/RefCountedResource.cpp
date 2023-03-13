#include <mutex>
#include "RefCountedResource.h"

template<typename T>
void RefCountedResource<T>::MarkUsed()
{
	std::unique_lock<std::shared_mutex> lock(mtx);
	if (count == 0)
	{
		resource->Load();
	}
	count++;
}

template<typename T>
void RefCountedResource<T>::MarkUnused()
{
	std::unique_lock<std::shared_mutex> lock(mtx);
	count--;
	if (count == 0)
	{
		resource->Unload();
	}
}

template<typename T>
 std::shared_lock<std::shared_mutex> RefCountedResource<T>::GetResource(T* value)
{
	 std::shared_lock<std::shared_mutex> lock(mtx);
	 T = value;
	 return std::move(lock); //move so it isn't destroyed/recreated.
}
