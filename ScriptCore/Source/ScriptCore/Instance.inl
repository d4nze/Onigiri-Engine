#include "Instance.hpp"
#include <type_traits>

template<class TComponent>
inline TComponent* Instance::addComponent()
{
	// static_assert(std::is_base_of<Component, TComponent> == true);
	return reinterpret_cast<TComponent*>(addComponent(ComponentHolder{ new TComponent, typeid(TComponent) }));
}

template<class TComponent>
inline TComponent* Instance::getComponent()
{
	Component* component = getComponent(typeid(TComponent));
	if (component != nullptr)
	{
		return reinterpret_cast<TComponent*>(component);
	}
	return nullptr;
}

template<class TComponent>
inline const TComponent* Instance::getComponent() const
{
	Component* component = getComponent(typeid(TComponent));
	if (component != nullptr)
	{
		return reinterpret_cast<TComponent*>(component);
	}
	return nullptr;
}
