#include "InstanceIterator.hpp"
#include "Instance.hpp"

ScriptCore::InstanceIterator::InstanceIterator(const Instance* parent, const std::vector<Instance*>& instances, std::int32_t startingPoint)
    : m_parent(parent)
    , m_instances(instances)
    , m_index(startingPoint)
{
    if (m_index < m_instances.size())
    {
        moveToNextComponent();
    }
}

ScriptCore::Instance* ScriptCore::InstanceIterator::operator*()
{
    return m_instances[m_index];
}

const ScriptCore::Instance* ScriptCore::InstanceIterator::operator*() const
{
    return m_instances[m_index + 1];
}

ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator++()
{
    m_index++;
    moveToNextComponent();
    return *this;
}

const ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator++() const
{
    m_index++;
    moveToNextComponent();
    return *this;
}

ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator--()
{
    if (m_index != -1)
    {
        m_index--;
        moveToPreviusComponent();
    }
    return *this;
}

const ScriptCore::InstanceIterator& ScriptCore::InstanceIterator::operator--() const
{
    if (m_index != -1)
    {
        m_index--;
        moveToPreviusComponent();
    }
    return *this;
}

bool ScriptCore::InstanceIterator::operator==(const InstanceIterator& other) const
{
    return m_index == other.m_index;
}

bool ScriptCore::InstanceIterator::operator!=(const InstanceIterator& other) const
{
    return m_index != other.m_index;
}

void ScriptCore::InstanceIterator::moveToNextComponent() const
{
    for (; m_index < m_instances.size() && m_instances[m_index]->getParent() != m_parent; m_index++);
}

void ScriptCore::InstanceIterator::moveToPreviusComponent() const
{
    for (; m_instances[m_index]->getParent() != m_parent && m_index > 0; m_index--);
}
