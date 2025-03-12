#include "PathConfiguration.hpp"
#include "NameConfiguration.hpp"
#include "ApplicationCore/BrowseWindow.hpp"

#include <filesystem>
#include <imgui.h>

Launcher::ProjectCreation::PathConfiguration::PathConfiguration(ApplicationCore::FrameController& createController)
    : ApplicationCore::Frame(createController)
    , m_bufferSize(1024)
    , m_path(m_bufferSize, '\0')
    , m_errorType(ErrorType::NoError)
    , m_previousErrorType(m_errorType)
    , m_errorText("")
{}

void Launcher::ProjectCreation::PathConfiguration::reset()
{
    m_path = std::string(m_bufferSize, '\0');
    m_errorType = ErrorType::NoError;
    m_previousErrorType = m_errorType;
}

void Launcher::ProjectCreation::PathConfiguration::updateErrorType()
{
	m_errorType = ErrorType::NoError;
	std::filesystem::path systemPath = m_path;
	if (m_path[0] == '\0')
	{
		m_errorType = ErrorType::Empty;
	}
	else if (systemPath.is_relative())
	{
		m_errorType = ErrorType::RelativePath;
	}
	else if (!std::filesystem::exists(systemPath) && !std::filesystem::is_directory(systemPath))
	{
		m_errorType = ErrorType::InvalidPath;
	}
	else if (NameConfiguration* nameConfiguration = getNeighbour<NameConfiguration>())
	{
		std::string resultPath(m_path.c_str());
		resultPath += "\\";
		resultPath += nameConfiguration->getName();
		if (std::filesystem::exists(resultPath))
		{
			m_errorType = ErrorType::ProjectExists;
		}
	}
}

bool Launcher::ProjectCreation::PathConfiguration::hasError()
{
    return m_errorType != ErrorType::NoError;
}

bool Launcher::ProjectCreation::PathConfiguration::moveBack()
{
    return moveToNeighbour<NameConfiguration>();
}

const std::string& Launcher::ProjectCreation::PathConfiguration::getPath() const
{
    return m_path;
}

Launcher::ProjectCreation::PathConfiguration::ErrorType Launcher::ProjectCreation::PathConfiguration::getError() const
{
    return m_errorType;
}

void Launcher::ProjectCreation::PathConfiguration::show()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", m_path.data(), m_bufferSize))
	{
		updateErrorType();
	}
	ImGui::SameLine();
	if (ImGui::Button("Browse", ImVec2(80, 0)))
	{
		std::filesystem::path path = ApplicationCore::BrowseWindow::selectFolder();
		if (!path.empty())
		{
			std::string sPath = path.string();
			m_path = sPath;
			m_path.resize(m_bufferSize);
			updateErrorType();
		}
	}
	if (m_errorType != ErrorType::NoError)
	{
		if (m_errorType != m_previousErrorType)
		{
			m_previousErrorType = m_errorType;
			updateErrorText();
		}
		showError();
	}
}

void Launcher::ProjectCreation::PathConfiguration::showError()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
	ImGui::Text(m_errorText.c_str());
	ImGui::PopStyleColor();
}

void Launcher::ProjectCreation::PathConfiguration::updateErrorText()
{
	switch (m_errorType)
	{
	case ErrorType::Empty:
		m_errorText = "Please select project folder";
		break;
	case ErrorType::RelativePath:
		m_errorText = "Path must be absolute";
		break;
	case ErrorType::ProjectExists:
		m_errorText = "There is an already existing project with this name";
		break;
	case ErrorType::InvalidPath:
		m_errorText = "Invalid path";
		break;
	}
}
