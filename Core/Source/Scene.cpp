#include "Scene.hpp"
#include "Instance.hpp"
#include "StepComponent.hpp"

Scene::Scene(sf::RenderTarget& renderTarget) : m_renderTarget(renderTarget)
{}

Scene::~Scene()
{
    for (Instance* instance : m_instances)
    {
        delete instance;
    }
    for (ComponentHolder componentHolder : m_components)
    {
        delete componentHolder.component;
    }
}

sf::RenderTarget& Scene::getRenderTarget()
{
    return m_renderTarget;
}

const sf::RenderTarget& Scene::getRenderTarget() const
{
    return m_renderTarget;
}

Instance* Scene::createInstance(const std::string& instanceName)
{
    return createInstance(instanceName, nullptr);
}

Instance* Scene::getInstance(const std::string& instanceName, std::uint32_t depth)
{
    return getInstance(instanceName, nullptr, depth);
}

const Instance* Scene::getInstance(const std::string& instanceName, std::uint32_t depth) const
{
    return getInstance(instanceName, nullptr, depth);
}

bool Scene::destroyInstance(Instance* instance)
{
    for (std::vector<Instance*>::iterator it = m_instances.begin(); it != m_instances.end(); it++)
    {
        if (*it == instance)
        {
            delete instance;
            m_instances.erase(it);
            return true;
        }
    }
    return false;
}

InstanceIterator Scene::begin()
{
    return begin(nullptr);
}

InstanceIterator Scene::end()
{
    return end(nullptr);
}

const InstanceIterator Scene::begin() const
{
    return begin(nullptr);
}

const InstanceIterator Scene::end() const
{
    return end(nullptr);
}

Instance* Scene::createInstance(const std::string& instanceName, Instance* instanceParent)
{
    Instance* instance = new Instance(*this, instanceName, instanceParent);
    m_instances.push_back(instance);
    return instance;
}

Instance* Scene::getInstance(const std::string& instanceName, Instance* startingPoint, std::uint32_t depth) const
{
    std::vector<Instance*> instances = m_instances;
    for (std::uint32_t i = 0; i <= depth && !instances.empty(); i++)
    {
        std::vector<Instance*> nextDepth;
        for (Instance* instance : instances)
        {
            if (instance->getParent() == startingPoint)
            {
                if (instance->m_name == instanceName)
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

void Scene::step()
{
    while (!m_createComponents.empty())
    {
        ComponentHolder componentHolder = m_createComponents.front();
        m_createComponents.pop();
        componentHolder.component->create();
        m_components.push_back(componentHolder);
        StepComponent* stepComponent = dynamic_cast<StepComponent*>(componentHolder.component);
        if (stepComponent == nullptr)
        {
            continue;
        }

        Instance* componentInstance = &componentHolder.component->getInstance();
        std::size_t instanceIndex = 0;
        for (; instanceIndex < m_instances.size() && m_instances[instanceIndex] != componentInstance; instanceIndex++);

        std::size_t insertIndex = 0;
        for (; insertIndex < m_stepComponents.size(); insertIndex++)
        {
            StepComponent* otherStepComponent = m_stepComponents[insertIndex];
            if (otherStepComponent->getScenePriority() < stepComponent->getScenePriority())
            {
                break;
            }
            std::size_t otherInstanceIndex = 0;
            for (; otherInstanceIndex < m_instances.size()
                 && m_instances[otherInstanceIndex] != m_instances[insertIndex];
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
        m_stepComponents.insert(m_stepComponents.begin() + insertIndex, stepComponent);
    }

    for (StepComponent* stepComponent : m_stepComponents)
    {
        stepComponent->step();
    }

    while (!m_destroyComponents.empty())
    {
        Component* component = m_destroyComponents.front();
        component->destroy();
        for (std::vector<ComponentHolder>::iterator it = m_components.begin(); it != m_components.end(); it++)
        {
            if (it->component == component)
            {
                m_components.erase(it);
                break;
            }
        }
        if (StepComponent* stepComponent = dynamic_cast<StepComponent*>(component))
        {
            for (std::vector<StepComponent*>::iterator it = m_stepComponents.begin(); it != m_stepComponents.end(); it++)
            {
                if (*it == stepComponent)
                {
                    m_stepComponents.erase(it);
                    break;
                }
            }
        }
        delete component;
    }
}

InstanceIterator Scene::begin(Instance* parent)
{
    return InstanceIterator(parent, m_instances);
}

InstanceIterator Scene::end(Instance* parent)
{
    return InstanceIterator(parent, m_instances, m_instances.size());
}

const InstanceIterator Scene::begin(const Instance* parent) const
{
    return InstanceIterator(parent, m_instances);
}

const InstanceIterator Scene::end(const Instance* parent) const
{
    return InstanceIterator(parent, m_instances, m_instances.size());
}
