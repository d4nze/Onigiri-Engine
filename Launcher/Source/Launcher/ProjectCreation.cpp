#include "ProjectCreation.hpp"
#include "ProjectSelection.hpp"

#include <imgui.h>

Launcher::ProjectCreation::ProjectCreation(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
{
	frameController.addNeighbour<ProjectSelection>(this);
}

void Launcher::ProjectCreation::show()
{
	ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
	// Name and path configurations here...
	ImGui::EndChild();

	const float buttonWidth = 80.f;
	const float spacing = 10.f;
	const float windowWidth = ImGui::GetWindowWidth();
	const float totalButtonsWidth = buttonWidth * 2.f + spacing;

	if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
	{
		moveToNeighbour<ProjectSelection>();
	}
	ImGui::SameLine(windowWidth - totalButtonsWidth - ImGui::GetStyle().ItemSpacing.x);
	ImGui::BeginDisabled();
	if (ImGui::Button("Back", ImVec2(buttonWidth, 0))) {}
	ImGui::SameLine();
	if (ImGui::Button("Next", ImVec2(buttonWidth, 0))) {}
	ImGui::EndDisabled();
}
