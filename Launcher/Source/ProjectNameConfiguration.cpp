#include "ProjectNameConfiguration.hpp"
#include "ProjectCreation.hpp"

#include <cstdint>
#include <imgui.h>

ProjectNameConfiguration::ProjectNameConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_bufferSize(256)
	, m_nameBuffer("MyProject")
{}

void ProjectNameConfiguration::update()
{
	ImGui::TextUnformatted("Enter project's name");
	ImGui::InputText("##Project Name Input", m_nameBuffer, m_bufferSize);
	updateErrorLog();
	if (!m_error.empty())
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_error.c_str());
		ImGui::PopStyleColor();
	}
}

void ProjectNameConfiguration::reset()
{
	std::strncpy(m_nameBuffer, "MyProject", m_bufferSize);
}

void ProjectNameConfiguration::updateErrorLog()
{
	// TODO: Check for naming errors
}

std::string ProjectNameConfiguration::getName()
{
	return std::string(m_nameBuffer);
}
