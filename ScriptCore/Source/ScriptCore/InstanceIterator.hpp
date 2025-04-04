#pragma once
#include "CoreAPI.hpp"
#include <vector>

namespace ScriptCore
{
class SCRIPT_CORE_API Instance;

class SCRIPT_CORE_API InstanceIterator
{
private:
	InstanceIterator(const Instance* parent, const std::vector<Instance*>& instances, std::int32_t startingPoint = 0);

public:
	Instance* operator*();
	const Instance* operator*() const;
	InstanceIterator& operator++();
	const InstanceIterator& operator++() const;
	InstanceIterator& operator--();
	const InstanceIterator& operator--() const;
	bool operator==(const InstanceIterator& other) const;
	bool operator!=(const InstanceIterator& other) const;

private:
	void moveToNextComponent() const;
	void moveToPreviusComponent() const;

private:
	const Instance* mParent;
	const std::vector<Instance*>& mInstances;
	mutable std::size_t mIndex;

	friend class SCRIPT_CORE_API Scene;
};
}
