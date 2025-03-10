#include "ProjectSelection.hpp"
#include <imgui.h>

Launcher::ProjectSelection::ProjectSelection(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, m_projectsViewer(*this)
{}

Launcher::ProjectsViewer& Launcher::ProjectSelection::getProjectsView()
{
	return m_projectsViewer;
}

const Launcher::ProjectsViewer& Launcher::ProjectSelection::getProjectsView() const
{
	return m_projectsViewer;
}

void Launcher::ProjectSelection::show()
{
	ImGui::Button("Create Project");
	ImGui::SameLine();
	ImGui::Button("Import Project");
	m_projectsViewer.show();
}
