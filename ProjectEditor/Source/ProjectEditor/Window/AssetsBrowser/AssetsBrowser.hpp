#pragma once
#include "../../ResourceManager.hpp"
#include "../Window.hpp"

#include "Folder.hpp"
#include "InspectableFile.hpp"

#include <filesystem>
#include <optional>
#include <vector>

namespace filewatch
{
template<class StringType>
class FileWatch;
}

namespace ProjectEditor::Window::AssetsBrowser
{
class AssetsBrowser : public Window
{
public:
	AssetsBrowser(GUI& gui, bool open = false);
	~AssetsBrowser() override;

public:
	void show() override;

private:
	void initializeWatcher();
	void updateFolder(Folder& folder, std::uint32_t depth = 0);

	bool doDeselected() const;
	void deselect();

	bool doDeleteSelected() const;
	void deleteSelected();

private:
	ResourceManager& mResourceManager;

	Folder mAssetsFolder;
	bool mUpdateAssetsFolder;

	std::optional<std::filesystem::path> mSelectedPath;
	InspectableFile mSelectedFile;

	filewatch::FileWatch<std::string>* mAssetsWatcher;
};
}
