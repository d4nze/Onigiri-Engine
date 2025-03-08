#include "ProjectImporting.hpp"
#include "GUI.hpp"

#include <imgui.h>

ProjectImporting::ProjectImporting(GUI& launcherGUI) : m_gui(launcherGUI) {}

void ProjectImporting::update()
{
    ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
    ImGui::BeginDisabled();
    ImGui::Text("Importing is not yet supported");
    ImGui::EndDisabled();
    ImGui::EndChild();

    float buttonWidth = 80.0f;
    float spacing = 10.0f;
    float windowWidth = ImGui::GetWindowWidth();
    float totalButtonsWidth = buttonWidth * 2 + spacing;

    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
    {
        m_gui.getStateManager().setState<ProjectSelection>();
    }
    ImGui::SameLine(windowWidth - buttonWidth - ImGui::GetStyle().ItemSpacing.x);
    ImGui::BeginDisabled();
    if (ImGui::Button("Import", ImVec2(buttonWidth, 0))) {}
    ImGui::EndDisabled();
}

void ProjectImporting::reset() {}

GUI& ProjectImporting::getGUI()
{
	return m_gui;
}

const GUI& ProjectImporting::getGUI() const
{
	return m_gui;
}
