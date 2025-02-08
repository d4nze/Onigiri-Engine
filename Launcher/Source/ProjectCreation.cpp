#include "ProjectCreation.hpp"
#include "LauncherGUI.hpp"
#include "ProjectSelection.hpp"

#include <imgui.h>

ProjectCreation::ProjectCreation(LauncherGUI& launcherGUI)
    : m_launcherGUI(launcherGUI)
    , m_step(typeid(ProjectNameConfiguration))
    , m_nameConfiguration(*this)
{}

void ProjectCreation::update()
{
    ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
    m_nameConfiguration.update();
    ImGui::EndChild();

    float buttonWidth = 80.0f;
    float spacing = 10.0f;
    float windowWidth = ImGui::GetWindowWidth();
    float totalButtonsWidth = buttonWidth * 2 + spacing;

    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
    {
        m_launcherGUI.getStateManager().setState<ProjectSelection>();
        reset();
    }

    ImGui::SameLine(windowWidth - totalButtonsWidth - ImGui::GetStyle().ItemSpacing.x);
    if (m_step.is<ProjectNameConfiguration>())
    {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0)));
    ImGui::EndDisabled();

    ImGui::SameLine();
    if (ImGui::Button("Next", ImVec2(buttonWidth, 0)));
}

void ProjectCreation::reset()
{
    m_nameConfiguration.reset();
}
