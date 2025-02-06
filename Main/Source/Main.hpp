#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Scene.hpp"

std::int32_t main();

class Main
{
public:
	Main();
	~Main() = default;

public:
	void run();

private:
	void initScene();

	void loop();
	void pollEvents();

private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	Scene m_scene;
};
