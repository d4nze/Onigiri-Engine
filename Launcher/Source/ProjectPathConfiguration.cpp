#include "ProjectPathConfiguration.hpp"
#include "Application/BrowseWindow.hpp"
#include "ProjectCreation.hpp"
#include "LauncherGUI.hpp"
#include "LauncherApplication.hpp"

#include <imgui.h>

const char* ProjectPathConfiguration::ErrorVariation::noError = "";
const char* ProjectPathConfiguration::ErrorVariation::empty = "Please select project folder";
const char* ProjectPathConfiguration::ErrorVariation::relativePath = "Path must be absolute";
const char* ProjectPathConfiguration::ErrorVariation::projectExists = "There is an already exiting project with this name";
const char* ProjectPathConfiguration::ErrorVariation::invalidPath = "Invalid path";

ProjectPathConfiguration::ProjectPathConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_error(ErrorVariation::noError)
	, m_bufferSize(256)
	, m_pathBuffer("\0")
{
	reset();
}

void ProjectPathConfiguration::update()
{
	ImGui::TextUnformatted("Choose folder for project");
	if (ImGui::InputTextWithHint("##Project Name Input", "Path here...", m_pathBuffer, m_bufferSize))
	{
		updateErrorLog();
	}
	ImGui::SameLine();
	if (ImGui::Button("Browse", ImVec2(80, 0)))
	{
		std::filesystem::path path = BrowseWindow::selectFolder();
		if (!path.empty())
		{
			std::string sPath = path.string();
			std::strncpy(m_pathBuffer, sPath.c_str(), m_bufferSize);
			updateErrorLog();
		}
	}
	if (m_error != ErrorVariation::noError)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_error.c_str());
		ImGui::PopStyleColor();
	}
}

void ProjectPathConfiguration::reset()
{
	static ProjectsHolder& projects = m_projectCreation.getGUI().getProjectSelection().getProjectsHolder();
	if (projects.begin() != projects.end())
	{
		Project lastProject = *projects.begin();
		std::strncpy(m_pathBuffer, lastProject.getPath().c_str(), m_bufferSize);
		m_error = "";
	}
	else
	{
		std::strncpy(m_pathBuffer, "\0", m_bufferSize);
		m_error = "Please select";
	}
}

void ProjectPathConfiguration::updateErrorLog()
{
	m_error = ErrorVariation::noError;
	std::filesystem::path path = m_pathBuffer;
	if (m_pathBuffer[0] == '\0')
	{
		m_error = ErrorVariation::empty;
	}
	else if (path.is_relative())
	{
		m_error = ErrorVariation::relativePath;
	}
	else if (!std::filesystem::exists(path) && !std::filesystem::is_directory(path))
	{
		m_error = ErrorVariation::invalidPath;
	}
	// else if (std::filesystem::exists(m_projectCreation.getName())) { ... }
}

std::string ProjectPathConfiguration::getName()
{
	return std::string(m_pathBuffer);
}

bool ProjectPathConfiguration::hasError() const
{
	return m_error != ErrorVariation::noError;
}
