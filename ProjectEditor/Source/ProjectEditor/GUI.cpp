#include "GUI.hpp"

#include <imgui.h>
#include <imgui-sfml.h>

ProjectEditor::GUI::GUI(Application& application)
	: mApplication(application)
	, mImGuiIO(ImGui::GetIO())
	, mMainFont(nullptr)
	, mMainMenuBar(*this)
	, mWindowHolder(*this)
{
	mImGuiIO.IniFilename = "ProjectEditor.ini";
	mImGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	initializeFont();
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

void ProjectEditor::GUI::initializeFont()
{
	ImFontGlyphRangesBuilder builder;
	builder.AddRanges(mImGuiIO.Fonts->GetGlyphRangesDefault());
	builder.AddRanges(mImGuiIO.Fonts->GetGlyphRangesCyrillic());
	builder.AddChar(0x2013); // en dash
	builder.AddChar(0x2014); // em dash
	builder.AddChar(0x2015); // horizontal bar
	builder.AddChar(0x2026); // ellipsis …
	builder.AddChar(0x00AB); // «
	builder.AddChar(0x00BB); // »
	ImVector<ImWchar> fullGlyphRanges;
	builder.BuildRanges(&fullGlyphRanges);
	std::filesystem::path fontPath = "Fonts";
	fontPath /= "consola.ttf";
	mMainFont = mImGuiIO.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 14.0f, nullptr, fullGlyphRanges.Data);
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
