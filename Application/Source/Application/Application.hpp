#pragma once
#include "ApplicationAPI.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class APPLICATION_API Application
{
public:
	Application(const sf::VideoMode& windowResolution, const std::string& windowTitle);
	~Application();

public:
	void run();

	sf::RenderWindow& getWindow();
	const sf::RenderWindow& getWindow() const;

protected:
	virtual void update() = 0;
	virtual void handleEvent(const std::optional<sf::Event> event);

protected:
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;
};
