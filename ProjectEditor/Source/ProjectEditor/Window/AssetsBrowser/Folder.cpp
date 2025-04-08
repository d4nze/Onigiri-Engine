#include "Folder.hpp"

#include <imgui.h>

ProjectEditor::Window::AssetsBrowser::Folder::Folder(const std::filesystem::path& path)
	: mPath(path)
	, mSubFolders()
	, mFiles()
{}

void ProjectEditor::Window::AssetsBrowser::Folder::show(std::optional<std::filesystem::path>& selectedPath)
{
	std::string fileName = mPath.filename().string();
	ImGui::PushID(fileName.c_str());
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
	if (selectedPath == mPath)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (ImGui::TreeNodeEx(fileName.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			selectedPath = mPath;
		}
		for (auto& subFolder : mSubFolders)
		{
			subFolder.show(selectedPath);
		}
		for (auto& file : mFiles)
		{
			file.show(selectedPath);
		}
		ImGui::TreePop();
	}
	else if (ImGui::IsItemClicked())
	{
		selectedPath = mPath;
	}
	ImGui::PopID();
}

void ProjectEditor::Window::AssetsBrowser::Folder::clear()
{
	mSubFolders.clear();
	mFiles.clear();
}

void ProjectEditor::Window::AssetsBrowser::Folder::setPath(const std::filesystem::path& path)
{
	mPath = path;
}

ProjectEditor::Window::AssetsBrowser::Folder& ProjectEditor::Window::AssetsBrowser::Folder::addSubFolder(const std::filesystem::path& subFolderPath)
{
	return mSubFolders.emplace_back(subFolderPath);
}

void ProjectEditor::Window::AssetsBrowser::Folder::addFilePath(const std::filesystem::path& filePath)
{
	mFiles.push_back(filePath);
}

std::filesystem::path& ProjectEditor::Window::AssetsBrowser::Folder::getPath()
{
	return mPath;
}

std::vector<ProjectEditor::Window::AssetsBrowser::Folder>& ProjectEditor::Window::AssetsBrowser::Folder::getSubFolders()
{
	return mSubFolders;
}

std::vector<ProjectEditor::Window::AssetsBrowser::File>& ProjectEditor::Window::AssetsBrowser::Folder::getFiles()
{
	return mFiles;
}

const std::filesystem::path& ProjectEditor::Window::AssetsBrowser::Folder::getPath() const
{
	return mPath;
}

const std::vector<ProjectEditor::Window::AssetsBrowser::Folder>& ProjectEditor::Window::AssetsBrowser::Folder::getSubFolders() const
{
	return mSubFolders;
}

const std::vector<ProjectEditor::Window::AssetsBrowser::File>& ProjectEditor::Window::AssetsBrowser::Folder::getFiles() const
{
	return mFiles;
}
