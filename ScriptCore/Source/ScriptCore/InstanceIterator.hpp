#pragma once
#include "CoreAPI.hpp"
#include <vector>

namespace ScriptCore
{
class CORE_API Instance;

class CORE_API InstanceIterator
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
	const Instance* m_parent;
	const std::vector<Instance*>& m_instances;
	mutable std::size_t m_index;

	friend class CORE_API Scene;
};
}
