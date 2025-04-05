#include "Application.hpp"

#include <Windows.h>
#include <imgui.h>

ProjectEditor::Application::Application()
    : ApplicationCore::Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , mGUI(*this)
    , mSettings()
{
	ShowWindow(mWindow.getNativeHandle(), SW_MAXIMIZE);
}

void ProjectEditor::Application::update()
{
    mGUI.update();
}

ProjectEditor::Settings& ProjectEditor::Application::getSettings()
{
    return mSettings;
}

const ProjectEditor::Settings& ProjectEditor::Application::getSettings() const
{
    return mSettings;
}

ProjectEditor::GUI& ProjectEditor::Application::getGUI()
{
    return mGUI;
}

const ProjectEditor::GUI& ProjectEditor::Application::getGUI() const
{
    return mGUI;
}
