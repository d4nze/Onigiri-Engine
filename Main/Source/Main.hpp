#pragma once
#include <SFML/Graphics.hpp>
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
	Scene m_scene;
};
