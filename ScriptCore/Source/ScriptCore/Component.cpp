#include "Component.hpp"

ScriptCore::Component::Component() : m_instance(nullptr) {}

void ScriptCore::Component::create() {}

void ScriptCore::Component::destroy() {}

void ScriptCore::Component::save(nlohmann::json& data) {}

void ScriptCore::Component::load(nlohmann::json& data) {}

ScriptCore::Instance& ScriptCore::Component::getInstance()
{
	return *m_instance;
}

const ScriptCore::Instance& ScriptCore::Component::getInstance() const
{
	return *m_instance;
}
