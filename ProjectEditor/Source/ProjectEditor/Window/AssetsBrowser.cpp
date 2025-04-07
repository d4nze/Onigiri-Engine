#include "AssetsBrowser.hpp"
#include "Application.hpp"
#include "GUI.hpp"
#include "Inspector.hpp"

#include <filewatch/FileWatch.hpp>

/// FILE ///

ProjectEditor::Window::File::File(const std::filesystem::path& path) : mPath(path) {}

void ProjectEditor::Window::File::inspect()
{
	ImGui::Text("File");
	ImGui::Separator();
	ImGui::Text("Name: %s", mPath.filename().string().c_str());
	ImGui::Text("Size: %.2f KB", std::filesystem::file_size(mPath) / 1024.0f);
	if (mPath.has_extension())
	{
		ImGui::Text("Extension: %s", mPath.extension().string().c_str());
	}
}

void ProjectEditor::Window::File::show(Folder*& selectedFolder, File*& selectedFile)
{
	ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	if (selectedFile == this)
	{
		fileFlags |= ImGuiTreeNodeFlags_Selected;
	}
	ImGui::TreeNodeEx(mPath.filename().string().c_str(), fileFlags);
	if (ImGui::IsItemClicked())
	{
		selectedFolder = nullptr;
		selectedFile = this;
	}
}

void ProjectEditor::Window::File::setPath(const std::filesystem::path& path)
{
	mPath = path;
}

std::filesystem::path& ProjectEditor::Window::File::getPath()
{
	return mPath;
}

const std::filesystem::path& ProjectEditor::Window::File::getPath() const
{
	return mPath;
}

/// FOLDER ///

ProjectEditor::Window::Folder::Folder(const std::filesystem::path& path)
	: mPath(path)
	, mSubFolders()
	, mFiles()
{}

void ProjectEditor::Window::Folder::inspect()
{
	std::string folderName = "Folder name: " + mPath.filename().string();
	ImGui::Text(folderName.c_str());
}

void ProjectEditor::Window::Folder::show(Folder*& selectedFolder, File*& selectedFile)
{
	std::string fileName = mPath.filename().string();
	ImGui::PushID(fileName.c_str());
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
	if (selectedFolder == this)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (ImGui::TreeNodeEx(fileName.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			selectedFolder = this;
			selectedFile = nullptr;
		}
		for (auto& subFolder : mSubFolders)
		{
			subFolder.show(selectedFolder, selectedFile);
		}
		for (auto& file : mFiles)
		{
			file.show(selectedFolder, selectedFile);
		}
		ImGui::TreePop();
	}
	else if (ImGui::IsItemClicked())
	{
		selectedFolder = this;
		selectedFile = nullptr;
	}
	ImGui::PopID();
}

void ProjectEditor::Window::Folder::clear()
{
	mSubFolders.clear();
	mFiles.clear();
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
	mFiles.push_back(filePath);
}

std::filesystem::path& ProjectEditor::Window::Folder::getPath()
{
	return mPath;
}

std::vector<ProjectEditor::Window::Folder>& ProjectEditor::Window::Folder::getSubFolders()
{
	return mSubFolders;
}

std::vector<ProjectEditor::Window::File>& ProjectEditor::Window::Folder::getFiles()
{
	return mFiles;
}

const std::filesystem::path& ProjectEditor::Window::Folder::getPath() const
{
	return mPath;
}

const std::vector<ProjectEditor::Window::Folder>& ProjectEditor::Window::Folder::getSubFolders() const
{
	return mSubFolders;
}

const std::vector<ProjectEditor::Window::File>& ProjectEditor::Window::Folder::getFiles() const
{
	return mFiles;
}

/// ASSETS BROWSER ///

ProjectEditor::Window::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
	, mResourceManager(gui.getApplication().getResourceManager())
	, mAssetsFolder(mResourceManager.getRootPath() / "Assets")
	, mUpdateAssetsFolder(true)
	, mSelectedFile(nullptr)
	, mSelectedFolder(nullptr)
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
		mSelectedFile = nullptr;
		mSelectedFolder = nullptr;
		mAssetsFolder.clear();
		updateFolder(mAssetsFolder);
	}
	const Folder* prevFolder = mSelectedFolder;
	const File* prevFile = mSelectedFile;
	mAssetsFolder.show(mSelectedFolder, mSelectedFile);
	if (deselect())
	{
		mSelectedFile = nullptr;
		mSelectedFolder = nullptr;
	}
	else if (mSelectedFolder != prevFolder || mSelectedFile != prevFile)
	{
		Inspector& inspector = getGUI().getWindowHolder().getInspector();
		if (mSelectedFolder != nullptr)
		{
			inspector.setInspectable(mSelectedFolder);
		}
		else if (mSelectedFile != nullptr)
		{
			inspector.setInspectable(mSelectedFile);
		}
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
	Inspector& inspector = getGUI().getWindowHolder().getInspector();
	Inspectable* inspectable = inspector.getInspectable();
	if (inspectable == mSelectedFolder || inspectable == mSelectedFile)
	{
		inspector.setInspectable(nullptr);
	}
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
