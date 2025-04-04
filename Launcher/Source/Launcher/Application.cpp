#include "Application.hpp"
#include <imgui.h>

Launcher::Application::Application()
    : ApplicationCore::Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , mGUI(*this)
{}

void Launcher::Application::update()
{
    mGUI.update();
}
