#include "AssetsBrowser.hpp"
#include "Application.hpp"

#include <filewatch/FileWatch.hpp>

ProjectEditor::Window::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
	, mResourceManager(gui.getApplication().getResourceManager())
	, mAssetsFolder{mResourceManager.getRootPath() / "Assets", {}, {}}
	, mUpdateAssetsFolder(true)
	, mSelectedPath(std::nullopt)
	, mAssetsWatcher(nullptr)
{
	initializeWatcher();
}

ProjectEditor::Window::AssetsBrowser::~AssetsBrowser()
{
	delete mAssetsWatcher;
}

#include <iostream>

void ProjectEditor::Window::AssetsBrowser::show()
{
	if (mUpdateAssetsFolder)
	{
		std::cout << "Update called\n";
		mUpdateAssetsFolder = false;
		mSelectedPath = std::nullopt;
		mAssetsFolder.folders.clear();
		mAssetsFolder.files.clear();
		updateFolder(mAssetsFolder);
	}
	renderFolder(mAssetsFolder);
}

void ProjectEditor::Window::AssetsBrowser::initializeWatcher()
{
	auto lambda = [this](const std::string&, const filewatch::Event)
	{
		mUpdateAssetsFolder = true;
	};
	mAssetsWatcher = new filewatch::FileWatch<std::string>(mAssetsFolder.path.string(), lambda);
}

void ProjectEditor::Window::AssetsBrowser::updateFolder(Folder& folder, std::uint32_t depth)
{
	for (const auto& entry : std::filesystem::directory_iterator(folder.path))
	{
		if (std::filesystem::is_regular_file(entry.status()))
		{
			folder.files.push_back(entry.path());
		}
		else if (std::filesystem::is_directory(entry.status()) && depth < 100)
		{
			folder.folders.push_back({entry.path(), {}, {}});
			Folder& newFolder = folder.folders.back();
			updateFolder(newFolder);
		}
	}
}

void ProjectEditor::Window::AssetsBrowser::renderFolder(Folder& folder)
{
	std::string fileName = folder.path.filename().string();
	ImGui::PushID(fileName.c_str());
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
	if (mSelectedPath != std::nullopt && folder.path == mSelectedPath)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (ImGui::TreeNodeEx(fileName.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			mSelectedPath = folder.path;
		}
		for (auto& subFolder : folder.folders)
		{
			renderFolder(subFolder);
		}
		for (const auto& file : folder.files)
		{
			ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			if (mSelectedPath != std::nullopt && file == mSelectedPath)
			{
				fileFlags |= ImGuiTreeNodeFlags_Selected;
			}
			ImGui::TreeNodeEx(file.filename().string().c_str(), fileFlags);
			if (ImGui::IsItemClicked())
			{
				mSelectedPath = file;
			}
		}
		ImGui::TreePop();
	}
	else if (ImGui::IsItemClicked())
	{
		mSelectedPath = folder.path;
	}
	ImGui::PopID();
}
