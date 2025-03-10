#include "StepComponent.hpp"

ScriptCore::StepComponent::StepComponent(std::int32_t instancePriority, std::int32_t scenePriority)
	: m_instancePriority(instancePriority)
	, m_scenePriority(scenePriority)
{}

void ScriptCore::StepComponent::step() {}

void ScriptCore::StepComponent::setInstancePriority(std::int32_t priority)
{
	m_instancePriority = priority;
}

void ScriptCore::StepComponent::setScenePriority(std::int32_t priority)
{
	m_scenePriority = priority;
}

std::int32_t ScriptCore::StepComponent::getInstancePriority() const
{
	return m_instancePriority;
}

std::int32_t ScriptCore::StepComponent::getScenePriority() const
{
	return m_scenePriority;
}
