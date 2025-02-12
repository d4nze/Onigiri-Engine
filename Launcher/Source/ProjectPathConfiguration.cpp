#include "ProjectPathConfiguration.hpp"
#include "Application/BrowseWindow.hpp"
#include "ProjectCreation.hpp"

#include <imgui.h>

ProjectPathConfiguration::ProjectPathConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_bufferSize(256)
	, m_pathBuffer("\0")
{}

void ProjectPathConfiguration::update()
{
	ImGui::TextUnformatted("Choose folder for project");
	ImGui::InputTextWithHint("##Project Name Input", "Path here...", m_pathBuffer, m_bufferSize);
	ImGui::SameLine();
	if (ImGui::Button("Browse", ImVec2(80, 0)))
	{
		std::filesystem::path path = BrowseWindow::selectFolder();
		if (!path.empty())
		{
			std::string sPath = path.string();
			std::strncpy(m_pathBuffer, sPath.c_str(), sPath.size());
		}
	}
}

void ProjectPathConfiguration::reset()
{
	std::strncpy(m_pathBuffer, "\0", m_bufferSize);
}

std::string ProjectPathConfiguration::getName()
{
	return std::string(m_pathBuffer);
}
