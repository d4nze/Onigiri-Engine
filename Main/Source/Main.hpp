#pragma once
#include <SFML/Graphics.hpp>

#include "Environment.hpp"
#include "Script.hpp"

std::int32_t main();

class Main
{
public:
	Main();
	~Main() = default;

public:
	void run();

private:
	void loop();
	void pollEvents();

private:
	sf::RenderWindow m_window;
	Environment m_environment;
	Script* m_script;
};
