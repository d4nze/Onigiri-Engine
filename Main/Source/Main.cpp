#include "Main.hpp"
#include "MainApplication.hpp"

#ifdef DEBUG
#include <iostream>
#define SHOW_ERROR(message) std::cout << message << "\n";
#else
#defube SHOW_ERROR(message)
#endif

std::int32_t main()
{
	MainApplication application;
	try
	{
		application.run();
	}
	catch (std::exception exception)
	{
		SHOW_ERROR(exception.what());
	}
	return 0;
}

//#include "imgui.h"
//#include "imgui-SFML.h"
//
//#include <SFML/Graphics/CircleShape.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/System/Clock.hpp>
//#include <SFML/Window/Event.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
//    window.setFramerateLimit(60);
//    ImGui::SFML::Init(window);
//
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    sf::Clock deltaClock;
//    while (window.isOpen())
//    {
//        while (const auto event = window.pollEvent())
//        {
//            if (event->is<sf::Event::Closed>())
//            {
//                window.close();
//            }
//            ImGui::SFML::ProcessEvent(window, *event);
//        }
//
//        ImGui::SFML::Update(window, deltaClock.restart());
//
//        window.clear();
//        window.draw(shape);
//        ImGui::ShowDemoWindow();
//        ImGui::Begin("Hello, world!");
//        ImGui::Button("Look at this pretty button");
//        ImGui::End();
//        ImGui::SFML::Render(window);
//        window.display();
//    }
//
//    ImGui::SFML::Shutdown();
//}
