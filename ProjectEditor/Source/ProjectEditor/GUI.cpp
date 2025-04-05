#include "GUI.hpp"
#include "Window/Window.hpp"

#include <imgui-sfml.h>

ProjectEditor::GUI::GUI(Application& application)
	: mApplication(application)
	, mImGuiIO(ImGui::GetIO())
	, mMainFont(nullptr)
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
	for (auto[typeID, window] : mWindows)
	{
		bool open = window->isOpen();
		if (open && ImGui::Begin(window->getTitle(), &open))
		{
			window->show();
			ImGui::End();
		}
		window->setOpen(open);
	}
}

ProjectEditor::Application& ProjectEditor::GUI::getApplication()
{
	return mApplication;
}

const ProjectEditor::Application& ProjectEditor::GUI::getApplication() const
{
	return mApplication;
}

ProjectEditor::Window::Window* const ProjectEditor::GUI::getWindow(std::type_index typeID) const
{
	if (mWindows.find(typeID) != mWindows.end())
	{
		return mWindows.at(typeID);
	}
	return nullptr;
}
