#include "MainMenuBar.hpp"

#include "Window/AssetsBrowser/AssetsBrowser.hpp"
#include "Application.hpp"
#include "GUI.hpp"

#include <imgui.h>

ProjectEditor::MainMenuBar::MainMenuBar(GUI& gui) : mGUI(gui)
{}

void ProjectEditor::MainMenuBar::show()
{
	if (!ImGui::BeginMainMenuBar())
	{
		return;
	}
	showFileMenu();
	showWindowMenu();
	showHelpMenu();
	ImGui::EndMainMenuBar();
}

ProjectEditor::GUI& ProjectEditor::MainMenuBar::getGUI()
{
	return mGUI;
}

const ProjectEditor::GUI& ProjectEditor::MainMenuBar::getGUI() const
{
	return mGUI;
}

void ProjectEditor::MainMenuBar::showFileMenu()
{
	if (!ImGui::BeginMenu("File"))
	{
		return;
	}
	if (ImGui::MenuItem("Exit"))
	{
		mGUI.getApplication().getWindow().close();
	}
	ImGui::EndMenu();
}

void ProjectEditor::MainMenuBar::showWindowMenu()
{
	if (!ImGui::BeginMenu("Window"))
	{
		return;
	}
	Window::AssetsBrowser::AssetsBrowser& assetsBrowser = mGUI.getWindowHolder().getAssetsBrowser();
	if (ImGui::MenuItem("Assets Browser", nullptr, assetsBrowser.isOpen()))
	{
		assetsBrowser.open();
	}
	Window::Inspector& inspector = mGUI.getWindowHolder().getInspector();
	if (ImGui::MenuItem("Inspector", nullptr, inspector.isOpen()))
	{
		inspector.open();
	}
	ImGui::EndMenu();
}

void ProjectEditor::MainMenuBar::showHelpMenu()
{}
