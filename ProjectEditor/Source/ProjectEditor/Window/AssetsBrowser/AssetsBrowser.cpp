#include "AssetsBrowser.hpp"
#include "../Inspector.hpp"
#include "Application.hpp"
#include "GUI.hpp"

#include <filewatch/FileWatch.hpp>

/// FILE ///

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

/// FOLDER ///

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

/// INSPECTABLE FILE ///

ProjectEditor::Window::AssetsBrowser::InspectableFile::InspectableFile()
	: Inspectable()
	, File()
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
	ImGui::Text("Path: %s", getPath().string().c_str());
}

/// ASSETS BROWSER ///

ProjectEditor::Window::AssetsBrowser::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
	, mResourceManager(gui.getApplication().getResourceManager())
	, mAssetsFolder(mResourceManager.getRootPath() / "Assets")
	, mUpdateAssetsFolder(true)
	, mSelectedPath(std::nullopt)
	, mSelectedFile()
	, mAssetsWatcher(nullptr)
{
	initializeWatcher();
}

ProjectEditor::Window::AssetsBrowser::AssetsBrowser::~AssetsBrowser()
{
	delete mAssetsWatcher;
}

void ProjectEditor::Window::AssetsBrowser::AssetsBrowser::show()
{
	if (mUpdateAssetsFolder)
	{
		mUpdateAssetsFolder = false;
		deselect();
		mSelectedFile.update();
		mAssetsFolder.clear();
		updateFolder(mAssetsFolder);
	}
	const auto oldSelectedPath = mSelectedPath;
	mAssetsFolder.show(mSelectedPath);
	if (oldSelectedPath != mSelectedPath && !std::filesystem::is_directory(mSelectedPath.value()))
	{
		mSelectedFile.setPath(mSelectedPath.value());
		mSelectedFile.update();
		getGUI().getWindowHolder().getInspector().setInspectable(&mSelectedFile);
	}
	if (doDeselected())
	{
		deselect();
	}
	if (doDeleteSelected())
	{
		deleteSelected();
	}
}

void ProjectEditor::Window::AssetsBrowser::AssetsBrowser::initializeWatcher()
{
	auto lambda = [this](const std::string&, const filewatch::Event)
	{
		mUpdateAssetsFolder = true;
	};
	mAssetsWatcher = new filewatch::FileWatch<std::string>(mAssetsFolder.getPath().string(), lambda);
}

void ProjectEditor::Window::AssetsBrowser::AssetsBrowser::updateFolder(Folder& folder, std::uint32_t depth)
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

bool ProjectEditor::Window::AssetsBrowser::AssetsBrowser::doDeselected() const
{
	if (mSelectedPath == std::nullopt)
	{
		return false;
	}
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

void ProjectEditor::Window::AssetsBrowser::AssetsBrowser::deselect()
{
	mSelectedPath = std::nullopt;
}

bool ProjectEditor::Window::AssetsBrowser::AssetsBrowser::doDeleteSelected() const
{
	return mSelectedPath != std::nullopt && ImGui::IsKeyPressed(ImGuiKey_Delete);
}

void ProjectEditor::Window::AssetsBrowser::AssetsBrowser::deleteSelected()
{
	if (mSelectedPath == std::nullopt)
	{
		return;
	}
	std::filesystem::path selectedPath = mSelectedFile.getPath();
	if (std::filesystem::remove(selectedPath))
	{
		deselect();
	}
	mSelectedFile.update();
}
