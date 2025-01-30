#pragma once
#include "ComponentHolder.hpp"
#include "Component.hpp"
#include "InstanceIterator.hpp"
#include <string>
#include <typeindex>

class CORE_API Scene;

class CORE_API Instance
{
private:
	Instance(Scene& scene, const std::string& name, Instance* parent = nullptr);
	~Instance();

public:
	void setName(const std::string& name);
	const std::string& getName() const;
	Scene& getScene();
	const Scene& getScene() const;
	void setParent(Instance* parent);
	Instance* getParent() const;

	Instance* createInstance(const std::string& instanceName);
	Instance* getInstance(const std::string& instanceName, std::uint32_t depth);
	const Instance* getInstance(const std::string& instanceName, std::uint32_t depth = 0) const;
	bool destroyInstance(Instance* instance);

	template<class TComponent>
	TComponent* addComponent();
	template<class TComponent>
	TComponent* getComponent();
	template<class TComponent>
	const TComponent* getComponent() const;

	InstanceIterator begin();
	InstanceIterator end();
	const InstanceIterator begin() const;
	const InstanceIterator end() const;

private:
	Component* addComponent(ComponentHolder componentHolder);
	Component* getComponent(std::type_index typeID);

private:
	Scene& m_scene;
	std::string m_name;
	Instance* m_parent;

	friend Scene;
};

#include "Instance.inl"
