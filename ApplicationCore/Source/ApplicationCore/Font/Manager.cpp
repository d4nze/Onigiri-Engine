#include "Manager.hpp"

#include <filesystem>
#include <imgui.h>
#include <imgui-SFML.h>

ApplicationCore::Font::Manager::Manager(ImGuiIO& imGuiIO)
	: mMainFont(nullptr)
	, mBoldFont(nullptr)
	, mItalicFont(nullptr)
	, mBoldItalicFont(nullptr)
{
	ImFontGlyphRangesBuilder builder;
	builder.AddRanges(imGuiIO.Fonts->GetGlyphRangesDefault());
	builder.AddRanges(imGuiIO.Fonts->GetGlyphRangesCyrillic());
	builder.AddChar(0x2013); // en dash
	builder.AddChar(0x2014); // em dash
	builder.AddChar(0x2015); // horizontal bar
	builder.AddChar(0x2026); // ellipsis …
	builder.AddChar(0x00AB); // «
	builder.AddChar(0x00BB); // »
	ImVector<ImWchar> glyphRanges;
	builder.BuildRanges(&glyphRanges);

	std::filesystem::path fontPath = "Fonts";
	fontPath /= "consola.ttf";
	std::string sFontPath = fontPath.string();
	mMainFont = imGuiIO.Fonts->AddFontFromFileTTF(sFontPath.c_str(), 14.0f, nullptr, glyphRanges.Data);
	if (mMainFont == nullptr)
	{
		throw std::exception("Error initializing main font");
	}
	fontPath = "Fonts";
	fontPath /= "consolab.ttf";
	sFontPath = fontPath.string();
	mBoldFont = imGuiIO.Fonts->AddFontFromFileTTF(sFontPath.c_str(), 14.0f, nullptr, glyphRanges.Data);
	if (mBoldFont == nullptr)
	{
		throw std::exception("Error initializing bold font");
	}
	fontPath = "Fonts";
	fontPath /= "consolai.ttf";
	sFontPath = fontPath.string();
	mItalicFont = imGuiIO.Fonts->AddFontFromFileTTF(sFontPath.c_str(), 14.0f, nullptr, glyphRanges.Data);
	if (mItalicFont == nullptr)
	{
		throw std::exception("Error initializing italic font");
	}
	fontPath = "Fonts";
	fontPath /= "consolaz.ttf";
	sFontPath = fontPath.string();
	mBoldItalicFont = imGuiIO.Fonts->AddFontFromFileTTF(sFontPath.c_str(), 14.0f, nullptr, glyphRanges.Data);
	if (mBoldItalicFont == nullptr)
	{
		throw std::exception("Error initializing bold italic font");
	}

	imGuiIO.FontDefault = mMainFont;
	updateFontTexture();
}

ApplicationCore::Font::ScopedStyle ApplicationCore::Font::Manager::createScopedStyle(Style fontStyle)
{
    return ScopedStyle(*this, fontStyle);
}

void ApplicationCore::Font::Manager::pushFontStyle(Style fontStyle)
{
	switch (fontStyle)
	{
	case Style::Normal:
		ImGui::PushFont(mMainFont);
		break;
	case Style::Bold:
		ImGui::PushFont(mBoldFont);
		break;
	case Style::Italic:
		ImGui::PushFont(mItalicFont);
		break;
	case Style::BoldItalic:
		ImGui::PushFont(mBoldItalicFont);
		break;
	}
	updateFontTexture();
}

void ApplicationCore::Font::Manager::popFontStyle()
{
	ImGui::PopFont();
	updateFontTexture();
}

void ApplicationCore::Font::Manager::updateFontTexture()
{
	if (!ImGui::SFML::UpdateFontTexture())
	{
		throw std::exception("Error updating font's texture");
	}
}
