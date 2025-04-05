#include "Application.hpp"

#include <Windows.h>
#include <imgui.h>

ProjectEditor::Application::Application()
    : ApplicationCore::Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , mGUI(*this)
{
	ShowWindow(mWindow.getNativeHandle(), SW_MAXIMIZE);
}

void ProjectEditor::Application::update()
{
    mGUI.update();
}
