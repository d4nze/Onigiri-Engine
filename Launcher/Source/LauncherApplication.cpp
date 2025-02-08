#include "LauncherApplication.hpp"

#include <imgui.h>
#include <vector>

LauncherApplication::LauncherApplication() : Application(sf::VideoMode(sf::Vector2u(800, 600)))
{
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = "Launcher.ini";
}

static std::vector<std::pair<std::string, std::string>> projects = {
    { "Project Alpha",  "C:/Projects/Alpha" },
    { "Project Beta",   "C:/Projects/Beta" },
    { "Project Gamma",  "C:/Projects/Gamma" },
};

void LauncherApplication::update()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 windowSize = io.DisplaySize;

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
    for (size_t i = 0; i < projects.size(); i++)
    {
        ImGui::PushID(i);
        if (ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns, ImVec2(0, 40)));
        ImGui::PopID();

        ImGui::SameLine();
        const float x = ImGui::GetCursorPosX();
        ImGui::TextUnformatted(projects[i].first.c_str());
        ImGui::SetCursorPosX(x);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 20);
        ImGui::BeginDisabled();
        ImGui::TextUnformatted(projects[i].second.c_str());
        ImGui::EndDisabled();
        ImGui::Separator();
    }
    ImGui::EndChild();

    ImGui::End();
}
