#include "Component.hpp"

ScriptCore::Component::Component() : mInstance(nullptr) {}

void ScriptCore::Component::create() {}

void ScriptCore::Component::destroy() {}

void ScriptCore::Component::save(nlohmann::json& data) {}

void ScriptCore::Component::load(nlohmann::json& data) {}

ScriptCore::Instance& ScriptCore::Component::getInstance()
{
	return *mInstance;
}

const ScriptCore::Instance& ScriptCore::Component::getInstance() const
{
	return *mInstance;
}
