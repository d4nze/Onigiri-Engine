#include "ProjectSelection.hpp"
#include <imgui.h>

Launcher::ProjectSelection::ProjectSelection(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
{}

void Launcher::ProjectSelection::show()
{
	ImGui::Button("Create Project");
	ImGui::SameLine();
	ImGui::Button("Import Project");
}
