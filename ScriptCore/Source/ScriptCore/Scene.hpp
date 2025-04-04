#pragma once
#include "InstanceIterator.hpp"
#include "ComponentHolder.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <vector>
#include <queue>

namespace ScriptCore
{
class SCRIPT_CORE_API StepComponent;

class SCRIPT_CORE_API Scene
{
private:
	Scene(sf::RenderTarget& renderTarget);
	~Scene();

public:
	sf::RenderTarget& getRenderTarget();
	const sf::RenderTarget& getRenderTarget() const;

	Instance* createInstance(const std::string& instanceName);
	Instance* getInstance(const std::string& instanceName, std::uint32_t depth = 0);
	const Instance* getInstance(const std::string& instanceName, std::uint32_t depth = 0) const;
	bool destroyInstance(Instance* instance);

	InstanceIterator begin();
	InstanceIterator end();
	const InstanceIterator begin() const;
	const InstanceIterator end() const;

private:
	Instance* createInstance(const std::string& instanceName, Instance* instanceParent);
	Instance* getInstance(const std::string& instanceName, Instance* startingPoint, std::uint32_t depth = 0) const;
	void step();

	InstanceIterator begin(Instance* parent);
	InstanceIterator end(Instance* parent);
	const InstanceIterator begin(const Instance* parent) const;
	const InstanceIterator end(const Instance* parent) const;

private:
	sf::RenderTarget& mRenderTarget;
	std::vector<Instance*> mInstances;
	std::vector<ComponentHolder> mComponents;
	std::vector<StepComponent*> mStepComponents;
	std::queue<ComponentHolder> mCreateComponents;
	std::queue<Component*> mDestroyComponents;

	friend class Instance;
	friend class MainApplication;
};
}
