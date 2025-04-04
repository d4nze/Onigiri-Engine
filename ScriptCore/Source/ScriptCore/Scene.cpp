#include "Scene.hpp"
#include "Instance.hpp"
#include "StepComponent.hpp"

ScriptCore::Scene::Scene(sf::RenderTarget& renderTarget) : mRenderTarget(renderTarget)
{}

ScriptCore::Scene::~Scene()
{
    for (Instance* instance : mInstances)
    {
        delete instance;
    }
    for (ComponentHolder componentHolder : mComponents)
    {
        delete componentHolder.component;
    }
}

sf::RenderTarget& ScriptCore::Scene::getRenderTarget()
{
    return mRenderTarget;
}

const sf::RenderTarget& ScriptCore::Scene::getRenderTarget() const
{
    return mRenderTarget;
}

ScriptCore::Instance* ScriptCore::Scene::createInstance(const std::string& instanceName)
{
    return createInstance(instanceName, nullptr);
}

ScriptCore::Instance* ScriptCore::Scene::getInstance(const std::string& instanceName, std::uint32_t depth)
{
    return getInstance(instanceName, nullptr, depth);
}

const ScriptCore::Instance* ScriptCore::Scene::getInstance(const std::string& instanceName, std::uint32_t depth) const
{
    return getInstance(instanceName, nullptr, depth);
}

bool ScriptCore::Scene::destroyInstance(Instance* instance)
{
    for (std::vector<Instance*>::iterator it = mInstances.begin(); it != mInstances.end(); it++)
    {
        if (*it == instance)
        {
            delete instance;
            mInstances.erase(it);
            return true;
        }
    }
    return false;
}

ScriptCore::InstanceIterator ScriptCore::Scene::begin()
{
    return begin(nullptr);
}

ScriptCore::InstanceIterator ScriptCore::Scene::end()
{
    return end(nullptr);
}

const ScriptCore::InstanceIterator ScriptCore::Scene::begin() const
{
    return begin(nullptr);
}

const ScriptCore::InstanceIterator ScriptCore::Scene::end() const
{
    return end(nullptr);
}

ScriptCore::Instance* ScriptCore::Scene::createInstance(const std::string& instanceName, Instance* instanceParent)
{
    Instance* instance = new Instance(*this, instanceName, instanceParent);
    mInstances.push_back(instance);
    return instance;
}

ScriptCore::Instance* ScriptCore::Scene::getInstance(const std::string& instanceName, Instance* startingPoint, std::uint32_t depth) const
{
    std::vector<Instance*> instances = mInstances;
    for (std::uint32_t i = 0; i <= depth && !instances.empty(); i++)
    {
        std::vector<Instance*> nextDepth;
        for (Instance* instance : instances)
        {
            if (instance->getParent() == startingPoint)
            {
                if (instance->mName == instanceName)
                {
                    return instance;
                }
                nextDepth.push_back(instance);
            }
        }
        instances = nextDepth;
    }
    return nullptr;
}

void ScriptCore::Scene::step()
{
    while (!mCreateComponents.empty())
    {
        ComponentHolder componentHolder = mCreateComponents.front();
        mCreateComponents.pop();
        componentHolder.component->create();
        mComponents.push_back(componentHolder);
        StepComponent* stepComponent = dynamic_cast<StepComponent*>(componentHolder.component);
        if (stepComponent == nullptr)
        {
            continue;
        }

        Instance* componentInstance = &componentHolder.component->getInstance();
        std::size_t instanceIndex = 0;
        for (; instanceIndex < mInstances.size() && mInstances[instanceIndex] != componentInstance; instanceIndex++);

        std::size_t insertIndex = 0;
        for (; insertIndex < mStepComponents.size(); insertIndex++)
        {
            StepComponent* otherStepComponent = mStepComponents[insertIndex];
            if (otherStepComponent->getScenePriority() < stepComponent->getScenePriority())
            {
                break;
            }
            std::size_t otherInstanceIndex = 0;
            for (; otherInstanceIndex < mInstances.size()
                 && mInstances[otherInstanceIndex] != mInstances[insertIndex];
                 otherInstanceIndex++);
            if (otherInstanceIndex >= instanceIndex)
            {
                break;
            }
            if (&otherStepComponent->getInstance() != componentInstance)
            {
                break;
            }
            if (otherStepComponent->getInstancePriority() < stepComponent->getInstancePriority())
            {
                break;
            }
        }
        mStepComponents.insert(mStepComponents.begin() + insertIndex, stepComponent);
    }

    for (StepComponent* stepComponent : mStepComponents)
    {
        stepComponent->step();
    }

    while (!mDestroyComponents.empty())
    {
        Component* component = mDestroyComponents.front();
        component->destroy();
        for (std::vector<ComponentHolder>::iterator it = mComponents.begin(); it != mComponents.end(); it++)
        {
            if (it->component == component)
            {
                mComponents.erase(it);
                break;
            }
        }
        if (StepComponent* stepComponent = dynamic_cast<StepComponent*>(component))
        {
            for (std::vector<StepComponent*>::iterator it = mStepComponents.begin(); it != mStepComponents.end(); it++)
            {
                if (*it == stepComponent)
                {
                    mStepComponents.erase(it);
                    break;
                }
            }
        }
        delete component;
    }
}

ScriptCore::InstanceIterator ScriptCore::Scene::begin(Instance* parent)
{
    return InstanceIterator(parent, mInstances);
}

ScriptCore::InstanceIterator ScriptCore::Scene::end(Instance* parent)
{
    return InstanceIterator(parent, mInstances, mInstances.size());
}

const ScriptCore::InstanceIterator ScriptCore::Scene::begin(const Instance* parent) const
{
    return InstanceIterator(parent, mInstances);
}

const ScriptCore::InstanceIterator ScriptCore::Scene::end(const Instance* parent) const
{
    return InstanceIterator(parent, mInstances, mInstances.size());
}
