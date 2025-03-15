#include "ProjectSelection.hpp"
#include "../ProjectCreation/ProjectCreation.hpp"

#include <imgui.h>

Launcher::ProjectSelection::ProjectSelection::ProjectSelection(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, m_projectsViewer(*this)
{}

Launcher::ProjectSelection::ProjectsViewer& Launcher::ProjectSelection::ProjectSelection::getProjectsView()
{
	return m_projectsViewer;
}

const Launcher::ProjectSelection::ProjectsViewer& Launcher::ProjectSelection::ProjectSelection::getProjectsView() const
{
	return m_projectsViewer;
}

void Launcher::ProjectSelection::ProjectSelection::show()
{
	if (ImGui::Button("Create Project"))
	{
		moveToNeighbour<ProjectCreation::ProjectCreation>();
	}
	m_projectsViewer.show();
}
