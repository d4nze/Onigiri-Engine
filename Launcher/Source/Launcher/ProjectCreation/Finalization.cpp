#include "Finalization.hpp"
#include "NameConfiguration.hpp"
#include "PathConfiguration.hpp"
#include "ApplicationCore/Application.hpp"
#include "ApplicationCore/FrameController.hpp"

#include <imgui.h>

Launcher::ProjectCreation::Finalization::Finalization(ApplicationCore::FrameController& createController)
	: ApplicationCore::Frame(createController)
{}

void Launcher::ProjectCreation::Finalization::show()
{
	if (NameConfiguration* nameConfiguration = getNeighbour<NameConfiguration>())
	{
		std::string resultName = "Project's name: " + nameConfiguration->getName();
		ImGui::Text(resultName.c_str());
		if (PathConfiguration* pathConfiguration = getNeighbour<PathConfiguration>())
		{
			std::string resultPath = "Location: " + pathConfiguration->getPath() + "\\" + nameConfiguration->getName();
			ImGui::Text(resultPath.c_str());
		}
	}
}

bool Launcher::ProjectCreation::Finalization::moveBack()
{
	return moveToNeighbour<PathConfiguration>();
}
