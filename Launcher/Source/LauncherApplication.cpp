#include "LauncherApplication.hpp"

#include <imgui.h>
#include <vector>

LauncherApplication::LauncherApplication()
    : Application(sf::VideoMode(sf::Vector2u(800, 600)), "Launcher")
    , m_imGuiIO(ImGui::GetIO())
{
    m_imGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_imGuiIO.IniFilename = "Launcher.ini";

    m_projects = {
        { "Project Alpha",  "C:/Projects/Alpha" },
        { "Project Beta",   "C:/Projects/Beta" },
        { "Project Gamma",  "C:/Projects/Gamma" },
    };
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

    if (ImGui::Button("New Project"));
    ImGui::SameLine();
    if (ImGui::Button("Import Project"));
    ImGui::Separator();

    float listHeight = windowSize.y - 50;
    ImGui::BeginChild("Project List", ImVec2(0, listHeight), true);
    for (size_t i = 0; i < m_projects.size(); i++)
    {
        ImGui::PushID(i);
        m_projects[i].Update();
        ImGui::PopID();
    }
    ImGui::EndChild();

    ImGui::End();
}
