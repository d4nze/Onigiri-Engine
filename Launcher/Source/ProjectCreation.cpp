#include "ProjectCreation.hpp"
#include "LauncherGUI.hpp"
#include "ProjectSelection.hpp"

#include <imgui.h>

ProjectCreation::ProjectCreation(LauncherGUI& launcherGUI) : m_launcherGUI(launcherGUI) {}

void ProjectCreation::update()
{
	ImGui::Dummy(ImVec2(0, ImGui::GetContentRegionAvail().y - 25));

    float buttonWidth = 80.0f;
    float spacing = 10.0f;
    float windowWidth = ImGui::GetWindowWidth();
    float totalButtonsWidth = buttonWidth * 2 + spacing;

    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
    {
        m_launcherGUI.getStateManager().setState<ProjectSelection>();
    }
    ImGui::SameLine(windowWidth - totalButtonsWidth - ImGui::GetStyle().ItemSpacing.x);
    ImGui::BeginDisabled();
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0)));
    ImGui::EndDisabled();
    ImGui::SameLine();
    if (ImGui::Button("Next", ImVec2(buttonWidth, 0)));
}
