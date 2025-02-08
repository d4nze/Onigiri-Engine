#include "LauncherApplication.hpp"

#include <imgui.h>
#include <vector>

LauncherApplication::LauncherApplication()
    : Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , m_imGuiIO(ImGui::GetIO())
    , m_gui()
{
    m_imGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_imGuiIO.IniFilename = "Launcher.ini";
}

void LauncherApplication::update()
{
    ImVec2 windowSize = m_imGuiIO.DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin("Launcher", nullptr,
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoTitleBar);

    m_gui.update();

    ImGui::End();
}
