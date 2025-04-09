#include "Application.hpp"

Launcher::Application::Application()
    : ApplicationCore::Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , mGUI(*this)
{}

void Launcher::Application::update()
{
    mGUI.show();
}
