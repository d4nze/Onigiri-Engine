#pragma once
#include "CoreAPI.hpp"
#include <nlohmann/json.hpp>

namespace ScriptCore
{
class SCRIPT_CORE_API Instance;

class SCRIPT_CORE_API Component
{
public:
	Component();
	virtual ~Component() = default;

public:
	virtual void create();
	virtual void destroy();

	virtual void save(nlohmann::json& data);
	virtual void load(nlohmann::json& data);

	Instance& getInstance();
	const Instance& getInstance() const;

private:
	Instance* mInstance;
	friend Instance;
};
}
