#include "ProjectPathConfiguration.hpp"
#include "ApplicationCore/BrowseWindow.hpp"
#include "ProjectCreation.hpp"
#include "LauncherGUI.hpp"
#include "LauncherApplication.hpp"

#include <imgui.h>

ProjectPathConfiguration::ProjectPathConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_error(ErrorVariation::noError)
	, m_previousError(ErrorVariation::noError)
	, m_errorText("")
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
		updateErrorType();
	}
	ImGui::SameLine();
	if (ImGui::Button("Browse", ImVec2(80, 0)))
	{
		std::filesystem::path path = BrowseWindow::selectFolder();
		if (!path.empty())
		{
			std::string sPath = path.string();
			std::strncpy(m_pathBuffer, sPath.c_str(), m_bufferSize);
			updateErrorType();
		}
	}
	if (m_error != ErrorVariation::noError)
	{
		if (m_error != m_previousError)
		{
			updateErrorText();
		}
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_errorText.c_str());
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
		m_error = ErrorVariation::noError;
	}
	else
	{
		std::strncpy(m_pathBuffer, "\0", m_bufferSize);
		m_error = ErrorVariation::empty;
	}
}

void ProjectPathConfiguration::updateErrorType()
{
	if (m_error != ErrorVariation::noError)
	{
		m_previousError = m_error;
	}
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
	else
	{
		path += "\\";
		path += m_projectCreation.getNameConfiguration().getName();
		if (std::filesystem::exists(path))
		{
			m_error = ErrorVariation::projectExists;
		}
	}
}

void ProjectPathConfiguration::updateErrorText()
{
	m_previousError = m_error;
	switch (m_error)
	{
	case ErrorVariation::empty:
		m_errorText = "Please select project folder";
		break;
	case ErrorVariation::relativePath:
		m_errorText = "Path must be absolute";
		break;
	case ErrorVariation::projectExists:
		m_errorText = "There is an already existing project with this name";
		break;
	case ErrorVariation::invalidPath:
		m_errorText = "Invalid path";
		break;
	}
}

std::string ProjectPathConfiguration::getPath()
{
	return std::string(m_pathBuffer);
}

const std::string ProjectPathConfiguration::getPath() const
{
	return std::string(m_pathBuffer);
}

bool ProjectPathConfiguration::hasError() const
{
	return m_error != ErrorVariation::noError;
}
