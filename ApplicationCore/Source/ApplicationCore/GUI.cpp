#include "GUI.hpp"

#include <imgui.h>

ApplicationCore::GUI::GUI()
	: mImGuiIO(ImGui::GetIO())
	, mFontManager(mImGuiIO)
{}

ApplicationCore::Font::Manager& ApplicationCore::GUI::getFontManager()
{
	return mFontManager;
}

const ApplicationCore::Font::Manager& ApplicationCore::GUI::getFontManager() const
{
	return mFontManager;
}
