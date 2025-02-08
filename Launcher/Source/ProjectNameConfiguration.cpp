#include "ProjectNameConfiguration.hpp"
#include "ProjectCreation.hpp"

#include <imgui.h>

ProjectNameConfiguration::ProjectNameConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_bufferSize(256)
	, m_nameBuffer("My Project")
{}

void ProjectNameConfiguration::update()
{
	ImGui::TextUnformatted("Enter project's name");
	ImGui::InputText("##Project Name Input", m_nameBuffer, m_bufferSize);
}

void ProjectNameConfiguration::reset()
{
	std::strncpy(m_nameBuffer, "My Project", m_bufferSize);
}

std::string ProjectNameConfiguration::getName()
{
	return std::string(m_nameBuffer);
}
