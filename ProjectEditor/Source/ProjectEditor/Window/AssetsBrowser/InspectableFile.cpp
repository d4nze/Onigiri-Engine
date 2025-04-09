#include "InspectableFile.hpp"
#include "ApplicationCore/Font/Manager.hpp"

#include <imgui.h>

ProjectEditor::Window::AssetsBrowser::InspectableFile::InspectableFile(ApplicationCore::Font::Manager& fontManager)
	: Inspectable()
	, File()
	, mFontManager(fontManager)
	, mErrorText(std::nullopt)
	, mName()
	, mExtension()
	, mSize(0.0f)
{}

void ProjectEditor::Window::AssetsBrowser::InspectableFile::update()
{
	const std::filesystem::path& path = getPath();

	mErrorText = std::nullopt;
	if (!std::filesystem::exists(path))
	{
		mErrorText = "File does not exist";
		return;
	}
	if (!std::filesystem::is_regular_file(path))
	{
		mErrorText = "Path does not correspond to a regular file: " + path.string();
		return;
	}

	mName = path.stem().string();
	mExtension = path.extension().string();
	mSize = static_cast<float>(std::filesystem::file_size(path)) / 1024.0f;
}

void ProjectEditor::Window::AssetsBrowser::InspectableFile::inspect()
{
	ImGui::Text("File information");
	ImGui::Separator();
	if (mErrorText != std::nullopt)
	{
		ImGui::Text(mErrorText.value().c_str());
		return;
	}
	ImGui::Text("Name: %s", mName.c_str());
	ImGui::Text("Extension: %s", mExtension.c_str());
	ImGui::Text("Size: %.2f KB", mSize);
	{
		auto italicScope = mFontManager.createScopedStyle(ApplicationCore::Font::Style::Italic);
		ImGui::Text("Path: %s", getPath().string().c_str());
	}
}
