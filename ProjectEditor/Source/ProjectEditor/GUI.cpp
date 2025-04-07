#include "GUI.hpp"
#include "Window/AssetsBrowser.hpp"

#include <imgui.h>
#include <imgui-sfml.h>

ProjectEditor::GUI::GUI(Application& application)
	: mApplication(application)
	, mImGuiIO(ImGui::GetIO())
	, mMainFont(nullptr)
	, mWindowHolder(*this)
{
	mImGuiIO.IniFilename = "ProjectEditor.ini";
	mImGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	initializeFont();
}

void ProjectEditor::GUI::show()
{
	ImGui::DockSpaceOverViewport();
	mWindowHolder.show();
}

ProjectEditor::Application& ProjectEditor::GUI::getApplication()
{
	return mApplication;
}

ProjectEditor::Window::WindowHolder& ProjectEditor::GUI::getWindowHolder()
{
	return mWindowHolder;
}

const ProjectEditor::Application& ProjectEditor::GUI::getApplication() const
{
	return mApplication;
}

const ProjectEditor::Window::WindowHolder& ProjectEditor::GUI::getWindowHolder() const
{
	return mWindowHolder;
}

void ProjectEditor::GUI::initializeFont()
{
	static const ImWchar glyphRanges[] = {
		0x0020, 0x00FF,
		0x0400, 0x04FF,
		0
	};
	mMainFont = mImGuiIO.Fonts->AddFontFromFileTTF("vcrosdmonorus_vhsicons.ttf", 14.0f, nullptr, glyphRanges);
	if (!mMainFont)
	{
		throw std::exception("Error initializing font");
	}
	mImGuiIO.FontDefault = mMainFont;
	if (!ImGui::SFML::UpdateFontTexture())
	{
		throw std::exception("Error updating font's texture");
	}
}
