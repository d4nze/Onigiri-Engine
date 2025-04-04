#pragma once
#include "Component.hpp"

namespace ScriptCore
{
class SCRIPT_CORE_API StepComponent : public Component
{
public:
	StepComponent(std::int32_t instancePriority = 0, std::int32_t scenePriority = 0);

public:
	virtual void step();

	void setInstancePriority(std::int32_t priority);
	void setScenePriority(std::int32_t priority);
	std::int32_t getInstancePriority() const;
	std::int32_t getScenePriority() const;

private:
	std::int32_t mInstancePriority;
	std::int32_t mScenePriority;
};
}
