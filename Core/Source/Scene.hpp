#pragma once
#include "InstanceIterator.hpp"
#include "ComponentHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <vector>
#include <queue>

class CORE_API StepComponent;

class CORE_API Scene
{
private:
	Scene(sf::RenderTarget& renderTarget);
	~Scene();

public:
	sf::RenderTarget& getRenderTarget();
	const sf::RenderTarget& getRenderTarget() const;

	Instance* createInstance(const std::string& instanceName, Instance* instanceParent = nullptr);
	Instance* getInstance(const std::string& instanceName, std::uint32_t depth = 0);
	const Instance* getInstance(const std::string& instanceName, std::uint32_t depth = 0) const;
	bool destroyInstance(Instance* instance);

	InstanceIterator begin();
	InstanceIterator end();
	const InstanceIterator begin() const;
	const InstanceIterator end() const;

private:
	Instance* getInstance(const std::string& instanceName, Instance* startingPoint, std::uint32_t depth = 0) const;
	void step();

	InstanceIterator begin(Instance* parent);
	InstanceIterator end(Instance* parent);
	const InstanceIterator begin(const Instance* parent) const;
	const InstanceIterator end(const Instance* parent) const;

private:
	sf::RenderTarget& m_renderTarget;
	std::vector<Instance*> m_instances;
	std::vector<ComponentHolder> m_components;
	std::vector<StepComponent*> m_stepComponents;
	std::queue<ComponentHolder> m_createComponents;
	std::queue<Component*> m_destroyComponents;

	friend class Instance;
	friend class Main;
};
