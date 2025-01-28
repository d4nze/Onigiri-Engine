#include "Script.hpp"
#include <iostream>

void Script::create() {}

void Script::destroy() {}

void Script::step()
{
	std::cout << "Basic step event called\n";
}

Environment& Script::getEnvironment()
{
	return *m_environment;
}

const Environment& Script::getEnvironment() const
{
	return *m_environment;
}
