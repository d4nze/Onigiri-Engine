#include "ProjectSelection.hpp"
#include "../ProjectCreation/ProjectCreation.hpp"

#include <imgui.h>

Launcher::ProjectSelection::ProjectSelection::ProjectSelection(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, mProjectsViewer(*this)
{}

Launcher::ProjectSelection::ProjectsViewer& Launcher::ProjectSelection::ProjectSelection::getProjectsView()
{
	return mProjectsViewer;
}

const Launcher::ProjectSelection::ProjectsViewer& Launcher::ProjectSelection::ProjectSelection::getProjectsView() const
{
	return mProjectsViewer;
}

void Launcher::ProjectSelection::ProjectSelection::show()
{
	if (ImGui::Button("Create Project"))
	{
		moveToNeighbour<ProjectCreation::ProjectCreation>();
	}
	mProjectsViewer.show();
}
