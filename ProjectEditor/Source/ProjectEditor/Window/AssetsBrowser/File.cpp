#include "File.hpp"

#include <imgui.h>

ProjectEditor::Window::AssetsBrowser::File::File(const std::filesystem::path& path) : mPath(path) {}

void ProjectEditor::Window::AssetsBrowser::File::show(std::optional<std::filesystem::path>& selectedPath)
{
	ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	if (selectedPath == mPath)
	{
		fileFlags |= ImGuiTreeNodeFlags_Selected;
	}
	ImGui::TreeNodeEx(mPath.filename().string().c_str(), fileFlags);
	if (ImGui::IsItemClicked())
	{
		selectedPath = mPath;
	}
}

void ProjectEditor::Window::AssetsBrowser::File::setPath(const std::filesystem::path& path)
{
	mPath = path;
}

std::filesystem::path& ProjectEditor::Window::AssetsBrowser::File::getPath()
{
	return mPath;
}

const std::filesystem::path& ProjectEditor::Window::AssetsBrowser::File::getPath() const
{
	return mPath;
}
