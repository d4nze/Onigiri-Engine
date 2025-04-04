#include "StepComponent.hpp"

ScriptCore::StepComponent::StepComponent(std::int32_t instancePriority, std::int32_t scenePriority)
	: mInstancePriority(instancePriority)
	, mScenePriority(scenePriority)
{}

void ScriptCore::StepComponent::step() {}

void ScriptCore::StepComponent::setInstancePriority(std::int32_t priority)
{
	mInstancePriority = priority;
}

void ScriptCore::StepComponent::setScenePriority(std::int32_t priority)
{
	mScenePriority = priority;
}

std::int32_t ScriptCore::StepComponent::getInstancePriority() const
{
	return mInstancePriority;
}

std::int32_t ScriptCore::StepComponent::getScenePriority() const
{
	return mScenePriority;
}
