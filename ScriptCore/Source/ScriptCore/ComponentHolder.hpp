#pragma once
#include "CoreAPI.hpp"
#include <typeindex>

namespace ScriptCore
{
class CORE_API Component;

struct CORE_API ComponentHolder
{
	Component* component;
	std::type_index typeID;
};
}
