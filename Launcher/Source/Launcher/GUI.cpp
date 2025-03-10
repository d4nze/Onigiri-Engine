#include "GUI.hpp"
#include <imgui-sfml.h>

GUI::GUI(Application& application)
	: m_application(application)
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

void GUI::update()
{
}

Application& GUI::getApplication()
{
	return m_application;
}

const Application& GUI::getApplication() const
{
	return m_application;
}
