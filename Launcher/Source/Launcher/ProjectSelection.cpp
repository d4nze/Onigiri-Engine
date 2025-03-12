#include "ProjectSelection.hpp"
#include "ProjectCreation/ProjectCreation.hpp"

#include <imgui.h>

Launcher::ProjectSelection::ProjectSelection(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, m_projectsViewer(*this)
{
	if (frameController.addFrame<ProjectCreation::ProjectCreation>(new ProjectCreation::ProjectCreation(frameController)) != nullptr)
	{
		frameController.addNeighbour<ProjectCreation::ProjectCreation>(this);
	}
}

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
	if (ImGui::Button("Create Project"))
	{
		moveToNeighbour<ProjectCreation::ProjectCreation>();
	}
	ImGui::SameLine();
	ImGui::Button("Import Project");
	m_projectsViewer.show();
}
