
#include <shared_mutex>
template <typename T>
class RefCountedResource
{
public:

	RefCountedResource() : count(0), resource(nullptr) {}
	~RefCountedResource<T>()
	{
		if (resource != nullptr)
		{
			delete resource;
		}
	};
	void MarkUsed();
	void MarkUnused();
	std::shared_lock<std::shared_mutex> GetResource(T* value);

	std::shared_mutex mtx;

private:
	size_t count;
	T* resource;
};

