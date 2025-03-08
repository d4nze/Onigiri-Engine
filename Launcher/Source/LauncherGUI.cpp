#include "LauncherGUI.hpp"
#include <imgui-sfml.h>

LauncherGUI::LauncherGUI(Application& application)
	: m_application(application)
	, m_state(typeid(ProjectSelection))
	, m_projectSelection(*this)
	, m_projectCreation(*this)
	, m_projectImporting(*this)
	, m_mainFont(nullptr)
{
	ImGuiIO& io = ImGui::GetIO();
	static const ImWchar glyphRanges[] = {
		0x0020, 0x00FF,
		0x0400, 0x04FF,
		0
	};

	m_mainFont = io.Fonts->AddFontFromFileTTF("vcrosdmonorus_vhsicons.ttf", 14.0f, nullptr, glyphRanges);
	if (!m_mainFont)
	{
		throw std::exception("Error initializing font");
	}
	io.FontDefault = m_mainFont;
	if (!ImGui::SFML::UpdateFontTexture())
	{
		throw std::exception("Error updating font's texture");
	}
}

void LauncherGUI::update()
{
	if (m_state.is<ProjectSelection>())
	{
		m_projectSelection.update();
	}
	else if (m_state.is<ProjectCreation>())
	{
		m_projectCreation.update();
	}
	else if (m_state.is<ProjectImporting>())
	{
		m_projectImporting.update();
	}
}

Application& LauncherGUI::getApplication()
{
	return m_application;
}

const Application& LauncherGUI::getApplication() const
{
	return m_application;
}

LauncherState& LauncherGUI::getStateManager()
{
	return m_state;
}

const LauncherState& LauncherGUI::getStateManager() const
{
	return m_state;
}

ProjectSelection& LauncherGUI::getProjectSelection()
{
	return m_projectSelection;
}

const ProjectSelection& LauncherGUI::getProjectSelection() const
{
	return m_projectSelection;
}

ProjectCreation& LauncherGUI::getProjectCreation()
{
	return m_projectCreation;
}

const ProjectCreation& LauncherGUI::getProjectCreation() const
{
	return m_projectCreation;
}
