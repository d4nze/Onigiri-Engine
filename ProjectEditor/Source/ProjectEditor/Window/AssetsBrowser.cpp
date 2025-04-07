#include "AssetsBrowser.hpp"
#include "Application.hpp"

#include <filewatch/FileWatch.hpp>

/// FOLDER ///

ProjectEditor::Window::Folder::Folder(const std::filesystem::path& path)
	: mPath(path)
	, mSubFolders()
	, mFilePaths()
{}

void ProjectEditor::Window::Folder::show(std::optional<std::filesystem::path>& selectedPath)
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
		for (const auto& filePath : mFilePaths)
		{
			ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			if (selectedPath == filePath)
			{
				fileFlags |= ImGuiTreeNodeFlags_Selected;
			}
			ImGui::TreeNodeEx(filePath.filename().string().c_str(), fileFlags);
			if (ImGui::IsItemClicked())
			{
				selectedPath = filePath;
			}
		}
		ImGui::TreePop();
	}
	else if (ImGui::IsItemClicked())
	{
		selectedPath = mPath;
	}
	ImGui::PopID();
}

void ProjectEditor::Window::Folder::clear()
{
	mSubFolders.clear();
	mFilePaths.clear();
}

void ProjectEditor::Window::Folder::setPath(const std::filesystem::path& path)
{
	mPath = path;
}

ProjectEditor::Window::Folder& ProjectEditor::Window::Folder::addSubFolder(const std::filesystem::path& subFolderPath)
{
	return mSubFolders.emplace_back(subFolderPath);
}

void ProjectEditor::Window::Folder::addFilePath(const std::filesystem::path& filePath)
{
	mFilePaths.push_back(filePath);
}

std::filesystem::path& ProjectEditor::Window::Folder::getPath()
{
	return mPath;
}

std::vector<ProjectEditor::Window::Folder>& ProjectEditor::Window::Folder::getSubFolders()
{
	return mSubFolders;
}

std::vector<std::filesystem::path>& ProjectEditor::Window::Folder::getFilePaths()
{
	return mFilePaths;
}

const std::filesystem::path& ProjectEditor::Window::Folder::getPath() const
{
	return mPath;
}

const std::vector<ProjectEditor::Window::Folder>& ProjectEditor::Window::Folder::getSubFolders() const
{
	return mSubFolders;
}

const std::vector<std::filesystem::path>& ProjectEditor::Window::Folder::getFilePaths() const
{
	return mFilePaths;
}

/// ASSETS BROWSER ///

ProjectEditor::Window::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
	, mResourceManager(gui.getApplication().getResourceManager())
	, mAssetsFolder(mResourceManager.getRootPath() / "Assets")
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

void ProjectEditor::Window::AssetsBrowser::show()
{
	if (mUpdateAssetsFolder)
	{
		mUpdateAssetsFolder = false;
		mSelectedPath = std::nullopt;
		mAssetsFolder.clear();
		updateFolder(mAssetsFolder);
	}
	mAssetsFolder.show(mSelectedPath);
	if (deselect())
	{
		mSelectedPath = std::nullopt;
	}
}

void ProjectEditor::Window::AssetsBrowser::initializeWatcher()
{
	auto lambda = [this](const std::string&, const filewatch::Event)
	{
		mUpdateAssetsFolder = true;
	};
	mAssetsWatcher = new filewatch::FileWatch<std::string>(mAssetsFolder.getPath().string(), lambda);
}

void ProjectEditor::Window::AssetsBrowser::updateFolder(Folder& folder, std::uint32_t depth)
{
	for (const auto& entry : std::filesystem::directory_iterator(folder.getPath()))
	{
		if (std::filesystem::is_regular_file(entry.status()))
		{
			folder.addFilePath(entry.path());
		}
		else if (std::filesystem::is_directory(entry.status()) && depth < 100)
		{
			updateFolder(folder.addSubFolder(entry.path()));
		}
	}
}

bool ProjectEditor::Window::AssetsBrowser::deselect() const
{
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		return true;
	}
	if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
	{
		return true;
	}
	return false;
}
