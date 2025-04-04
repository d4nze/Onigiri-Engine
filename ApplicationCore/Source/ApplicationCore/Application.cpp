#include "Application.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

ApplicationCore::Application::Application(const sf::VideoMode& windowResolution, const std::string& windowTitle)
	: mWindow(windowResolution, windowTitle.c_str())
	, mDeltaClock()
{
	if (!ImGui::SFML::Init(mWindow))
	{
		throw std::exception("Error initializing ImGui");
	}
}

ApplicationCore::Application::~Application()
{
	ImGui::SFML::Shutdown();
}

void ApplicationCore::Application::run()
{
	while (mWindow.isOpen())
	{
		for (; const std::optional<sf::Event> event = mWindow.pollEvent(); handleEvent(event));
		ImGui::SFML::Update(mWindow, mDeltaClock.restart());
		mWindow.clear();
		update();
		ImGui::SFML::Render(mWindow);
		mWindow.display();
	}
}

sf::RenderWindow& ApplicationCore::Application::getWindow()
{
	return mWindow;
}

const sf::RenderWindow& ApplicationCore::Application::getWindow() const
{
	return mWindow;
}

void ApplicationCore::Application::handleEvent(const std::optional<sf::Event> event)
{
	ImGui::SFML::ProcessEvent(mWindow, *event);
	if (event->is<sf::Event::Closed>())
	{
		mWindow.close();
	}
}
