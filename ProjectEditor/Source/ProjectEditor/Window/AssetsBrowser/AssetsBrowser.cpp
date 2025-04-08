#include "AssetsBrowser.hpp"
#include "../Inspector.hpp"
#include "Application.hpp"
#include "GUI.hpp"

#include <filewatch/FileWatch.hpp>

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
