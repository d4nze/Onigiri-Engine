#pragma once
#include "CoreAPI.hpp"
#include <typeindex>

namespace ScriptCore
{
class SCRIPT_CORE_API Component;

struct SCRIPT_CORE_API ComponentHolder
{
	Component* component;
	std::type_index typeID;
};
}
