#include "GUI.hpp"
#include "ProjectSelection.hpp"

#include <imgui-sfml.h>

Launcher::GUI::GUI(Application& application)
	: m_application(application)
	, m_imGuiIO(ImGui::GetIO())
	, m_mainFont(nullptr)
	, m_mainFrame(new ProjectSelection(m_frameController))
	, m_frameController(*m_mainFrame)
{
	m_imGuiIO.IniFilename = "Launcher.ini";
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

void Launcher::GUI::update()
{
	ImVec2 windowSize = m_imGuiIO.DisplaySize;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin("Launcher", nullptr,
				 ImGuiWindowFlags_NoCollapse |
				 ImGuiWindowFlags_NoResize |
				 ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar);
	m_frameController.show();
	ImGui::End();
}

Launcher::Application& Launcher::GUI::getApplication()
{
	return m_application;
}

const Launcher::Application& Launcher::GUI::getApplication() const
{
	return m_application;
}
