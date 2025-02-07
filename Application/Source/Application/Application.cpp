#include "Application.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

Application::Application(const sf::VideoMode& windowResolution)
	: m_window(windowResolution, "Application")
	, m_deltaClock()
{
	if (!ImGui::SFML::Init(m_window))
	{
		throw std::exception("Error initializing ImGui");
	}
}

Application::~Application()
{
	ImGui::SFML::Shutdown();
}

void Application::run()
{
	while (m_window.isOpen())
	{
		for (; const std::optional<sf::Event> event = m_window.pollEvent(); handleEvent(event));
		ImGui::SFML::Update(m_window, m_deltaClock.reset());
		m_window.clear();
		update();
		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}

void Application::handleEvent(const std::optional<sf::Event> event)
{
	ImGui::SFML::ProcessEvent(m_window, *event);
	if (event->is<sf::Event::Closed>())
	{
		m_window.close();
	}
}
