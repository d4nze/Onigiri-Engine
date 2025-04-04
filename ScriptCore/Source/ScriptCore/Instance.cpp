#include "Instance.hpp"
#include "Scene.hpp"
#include "StepComponent.hpp"

ScriptCore::Instance::Instance(Scene& scene, const std::string& name, Instance* parent)
	: mScene(scene)
	, mName(name)
	, mParent(parent)
{}

ScriptCore::Instance::~Instance()
{
	for (std::size_t i = 0; i < mScene.mInstances.size(); i++)
	{
		if (mScene.mInstances[i]->mParent == this)
		{
			std::size_t prevSize = mScene.mInstances.size();
			delete mScene.mInstances[i];
			i -= prevSize - mScene.mInstances.size();
		}
	}

	for (ComponentHolder componentHolder : mScene.mComponents)
	{
		if (componentHolder.component->mInstance == this)
		{
			mScene.mDestroyComponents.push(componentHolder.component);
		}
	}
}

void ScriptCore::Instance::setName(const std::string& name)
{
	mName = name;
}

const std::string& ScriptCore::Instance::getName() const
{
	return mName;
}

ScriptCore::Scene& ScriptCore::Instance::getScene()
{
	return mScene;
}

const ScriptCore::Scene& ScriptCore::Instance::getScene() const
{
	return mScene;
}

void ScriptCore::Instance::setParent(Instance* parent)
{
	mParent = parent;
}

ScriptCore::Instance* ScriptCore::Instance::getParent() const
{
	return mParent;
}

ScriptCore::Instance* ScriptCore::Instance::createInstance(const std::string& instanceName)
{
	return mScene.createInstance(instanceName, this);
}

ScriptCore::Instance* ScriptCore::Instance::getInstance(const std::string& instanceName, std::uint32_t depth)
{
	return mScene.getInstance(instanceName, depth);
}

const ScriptCore::Instance* ScriptCore::Instance::getInstance(const std::string& instanceName, std::uint32_t depth) const
{
	return mScene.getInstance(instanceName, depth);
}

bool ScriptCore::Instance::destroyInstance(Instance* instance)
{
	return mScene.destroyInstance(instance);
}

ScriptCore::InstanceIterator ScriptCore::Instance::begin()
{
	return mScene.begin(this);
}

ScriptCore::InstanceIterator ScriptCore::Instance::end()
{
	return mScene.end(this);
}

const ScriptCore::InstanceIterator ScriptCore::Instance::begin() const
{
	return mScene.begin(this);
}

const ScriptCore::InstanceIterator ScriptCore::Instance::end() const
{
	return mScene.end(this);
}

ScriptCore::Component* ScriptCore::Instance::addComponent(ComponentHolder componentHolder)
{
	componentHolder.component->mInstance = this;
	mScene.mCreateComponents.push(componentHolder);
	return componentHolder.component;
}

ScriptCore::Component* ScriptCore::Instance::getComponent(std::type_index typeID)
{
	for (ComponentHolder componentHolder : mScene.mComponents)
	{
		if (componentHolder.component->mInstance == this &&
			componentHolder.typeID == typeID)
		{
			return componentHolder.component;
		}
	}
	return nullptr;
}
