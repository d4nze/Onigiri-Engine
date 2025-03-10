#include "StepComponent.hpp"

StepComponent::StepComponent(std::int32_t instancePriority, std::int32_t scenePriority)
	: m_instancePriority(instancePriority)
	, m_scenePriority(scenePriority)
{}

void StepComponent::step() {}

void StepComponent::setInstancePriority(std::int32_t priority)
{
	m_instancePriority = priority;
}

void StepComponent::setScenePriority(std::int32_t priority)
{
	m_scenePriority = priority;
}

std::int32_t StepComponent::getInstancePriority() const
{
	return m_instancePriority;
}

std::int32_t StepComponent::getScenePriority() const
{
	return m_scenePriority;
}
