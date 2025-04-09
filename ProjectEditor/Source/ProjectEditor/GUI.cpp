#include "GUI.hpp"

#include <imgui.h>

ProjectEditor::GUI::GUI(Application& application)
	: mApplication(application)
	, mMainMenuBar(*this)
	, mWindowHolder(*this)
{
	mImGuiIO.IniFilename = "ProjectEditor.ini";
	mImGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ProjectEditor::GUI::show()
{
	ImGui::DockSpaceOverViewport();
	mMainMenuBar.show();
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
