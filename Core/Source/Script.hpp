#pragma once
#include "CoreAPI.hpp"

class CORE_API Environment;

class CORE_API Script
{
public:
	virtual void create();
	virtual void destroy();
	virtual void step();

	Environment& getEnvironment();
	const Environment& getEnvironment() const;

private:
	Environment* m_environment;

	friend class Main;
};
