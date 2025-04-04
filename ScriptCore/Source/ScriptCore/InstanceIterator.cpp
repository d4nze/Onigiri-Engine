#include "InstanceIterator.hpp"
#include "Instance.hpp"

ScriptCore::InstanceIterator::InstanceIterator(const Instance* parent, const std::vector<Instance*>& instances, std::int32_t startingPoint)
    : mParent(parent)
    , mInstances(instances)
    , mIndex(startingPoint)
{
    if (mIndex < mInstances.size())
    {
        moveToNextComponent();
    }
}

ScriptCore::Instance* ScriptCore::InstanceIterator::operator*()
{
    return mInstances[mIndex];
}

const ScriptCore::Instance* ScriptCore::InstanceIterator::operator*() const
{
    return mInstances[mIndex + 1];
}

ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator++()
{
    mIndex++;
    moveToNextComponent();
    return *this;
}

const ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator++() const
{
    mIndex++;
    moveToNextComponent();
    return *this;
}

ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator--()
{
    if (mIndex != -1)
    {
        mIndex--;
        moveToPreviusComponent();
    }
    return *this;
}

const ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator--() const
{
    if (mIndex != -1)
    {
        mIndex--;
        moveToPreviusComponent();
    }
    return *this;
}

bool ScriptCore::InstanceIterator::operator==(const InstanceIterator& other) const
{
    return mIndex == other.mIndex;
}

bool ScriptCore::InstanceIterator::operator!=(const InstanceIterator& other) const
{
    return mIndex != other.mIndex;
}

void ScriptCore::InstanceIterator::moveToNextComponent() const
{
    for (; mIndex < mInstances.size() && mInstances[mIndex]->getParent() != mParent; mIndex++);
}

void ScriptCore::InstanceIterator::moveToPreviusComponent() const
{
    for (; mInstances[mIndex]->getParent() != mParent && mIndex > 0; mIndex--);
}
