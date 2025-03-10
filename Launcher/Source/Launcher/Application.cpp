#include "Application.hpp"

#include <imgui.h>
#include <vector>

Launcher::Application::Application()
    : ApplicationCore::Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , m_gui(*this)
{}

void Launcher::Application::update()
{
    m_gui.update();
}
