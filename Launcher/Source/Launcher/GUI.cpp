#include "GUI.hpp"
#include "ProjectSelection/ProjectSelection.hpp"
#include "ProjectCreation/ProjectCreation.hpp"

#include <imgui-sfml.h>

Launcher::GUI::GUI(Application& application)
	: mApplication(application)
	, mImGuiIO(ImGui::GetIO())
	, mMainFont(nullptr)
	, mFrameController((ApplicationCore::Application&)mApplication)
{
	ApplicationCore::Frame* projectSelection = mFrameController.addFrame<ProjectSelection::ProjectSelection>(new ProjectSelection::ProjectSelection(mFrameController));
	if (projectSelection == nullptr || !mFrameController.setCurrentFrame<ProjectSelection::ProjectSelection>())
	{
		throw std::exception("Error initializing ProjectSelection");
	}
	ApplicationCore::Frame* projectCreation = mFrameController.addFrame<ProjectCreation::ProjectCreation>(new ProjectCreation::ProjectCreation(mFrameController));
	if (projectCreation == nullptr)
	{
		throw std::exception("Error initializing ProjectCreation");
	}

	if (!projectSelection->addNeighbour<ProjectCreation::ProjectCreation>())
	{
		throw std::exception("Error setting up connection: 'ProjectSelection -> ProjectCreation'");
	}
	if (!projectCreation->addNeighbour<ProjectSelection::ProjectSelection>())
	{
		throw std::exception("Error setting up connection: 'ProjectCreation -> ProjectSelection'");
	}

	mImGuiIO.IniFilename = "Launcher.ini";
	ImGuiIO& io = ImGui::GetIO();
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

void Launcher::GUI::update()
{
	ImVec2 windowSize = mImGuiIO.DisplaySize;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(windowSize);
	ImGui::Begin("Launcher", nullptr,
				 ImGuiWindowFlags_NoCollapse |
				 ImGuiWindowFlags_NoResize |
				 ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar);
	mFrameController.show();
	ImGui::End();
}

Launcher::Application& Launcher::GUI::getApplication()
{
	return mApplication;
}

const Launcher::Application& Launcher::GUI::getApplication() const
{
	return mApplication;
}
