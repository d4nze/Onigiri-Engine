#include "GUI.hpp"

#include <imgui-sfml.h>

ProjectEditor::GUI::GUI(Application& application)
	: mApplication(application)
	, mImGuiIO(ImGui::GetIO())
	, mMainFont(nullptr)
	, mFrameController((ApplicationCore::Application&)mApplication)
{
	mImGuiIO.IniFilename = "ProjectEditor.ini";
	ImGuiIO& io = ImGui::GetIO();
	mImGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	static const ImWchar glyphRanges[] = {
		0x0020, 0x00FF,
		0x0400, 0x04FF,
		0
	};
	mMainFont = io.Fonts->AddFontFromFileTTF("vcrosdmonorus_vhsicons.ttf", 14.0f, nullptr, glyphRanges);
	if (!mMainFont)
	{
		throw std::exception("Error initializing font");
	}
	io.FontDefault = mMainFont;
	if (!ImGui::SFML::UpdateFontTexture())
	{
		throw std::exception("Error updating font's texture");
	}
}

void ProjectEditor::GUI::update()
{
	ImGui::DockSpaceOverViewport();
	mFrameController.show();
}

ProjectEditor::Application& ProjectEditor::GUI::getApplication()
{
	return mApplication;
}

const ProjectEditor::Application& ProjectEditor::GUI::getApplication() const
{
	return mApplication;
}
