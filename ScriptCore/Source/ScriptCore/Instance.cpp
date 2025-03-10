#include "Instance.hpp"
#include "Scene.hpp"
#include "StepComponent.hpp"

ScriptCore::Instance::Instance(Scene& scene, const std::string& name, Instance* parent)
	: m_scene(scene)
	, m_name(name)
	, m_parent(parent)
{}

ScriptCore::Instance::~Instance()
{
	for (std::size_t i = 0; i < m_scene.m_instances.size(); i++)
	{
		if (m_scene.m_instances[i]->m_parent == this)
		{
			std::size_t prevSize = m_scene.m_instances.size();
			delete m_scene.m_instances[i];
			i -= prevSize - m_scene.m_instances.size();
		}
	}

	for (ComponentHolder componentHolder : m_scene.m_components)
	{
		if (componentHolder.component->m_instance == this)
		{
			m_scene.m_destroyComponents.push(componentHolder.component);
		}
	}
}

void ScriptCore::Instance::setName(const std::string& name)
{
	m_name = name;
}

const std::string& ScriptCore::Instance::getName() const
{
	return m_name;
}

ScriptCore::Scene& ScriptCore::Instance::getScene()
{
	return m_scene;
}

const ScriptCore::Scene& ScriptCore::Instance::getScene() const
{
	return m_scene;
}

void ScriptCore::Instance::setParent(Instance* parent)
{
	m_parent = parent;
}

ScriptCore::Instance* ScriptCore::Instance::getParent() const
{
	return m_parent;
}

ScriptCore::Instance* ScriptCore::Instance::createInstance(const std::string& instanceName)
{
	return m_scene.createInstance(instanceName, this);
}

ScriptCore::Instance* ScriptCore::Instance::getInstance(const std::string& instanceName, std::uint32_t depth)
{
	return m_scene.getInstance(instanceName, depth);
}

const ScriptCore::Instance* ScriptCore::Instance::getInstance(const std::string& instanceName, std::uint32_t depth) const
{
	return m_scene.getInstance(instanceName, depth);
}

bool ScriptCore::Instance::destroyInstance(Instance* instance)
{
	return m_scene.destroyInstance(instance);
}

ScriptCore::InstanceIterator ScriptCore::Instance::begin()
{
	return m_scene.begin(this);
}

ScriptCore::InstanceIterator ScriptCore::Instance::end()
{
	return m_scene.end(this);
}

const ScriptCore::InstanceIterator ScriptCore::Instance::begin() const
{
	return m_scene.begin(this);
}

const ScriptCore::InstanceIterator ScriptCore::Instance::end() const
{
	return m_scene.end(this);
}

ScriptCore::Component* ScriptCore::Instance::addComponent(ComponentHolder componentHolder)
{
	componentHolder.component->m_instance = this;
	m_scene.m_createComponents.push(componentHolder);
	return componentHolder.component;
}

ScriptCore::Component* ScriptCore::Instance::getComponent(std::type_index typeID)
{
	for (ComponentHolder componentHolder : m_scene.m_components)
	{
		if (componentHolder.component->m_instance == this &&
			componentHolder.typeID == typeID)
		{
			return componentHolder.component;
		}
	}
	return nullptr;
}
