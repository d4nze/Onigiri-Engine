#include "Component.hpp"

Component::Component() : m_instance(nullptr) {}

void Component::create() {}

void Component::destroy() {}

void Component::save(nlohmann::json& data) {}

void Component::load(nlohmann::json& data) {}

Instance& Component::getInstance()
{
	return *m_instance;
}

const Instance& Component::getInstance() const
{
	return *m_instance;
}
