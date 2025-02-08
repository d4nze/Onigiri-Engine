#include "ProjectPathConfiguration.hpp"
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

	}
}

void ProjectPathConfiguration::reset()
{
	std::strncpy(m_pathBuffer, "My Project", m_bufferSize);
}

std::string ProjectPathConfiguration::getName()
{
	return std::string(m_pathBuffer);
}
