#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

#include <filesystem>
#include <vector>
#include <optional>

namespace filewatch
{
template<class StringType>
class FileWatch;
}

namespace ProjectEditor::Window
{
struct Folder
{
	std::filesystem::path path;
	std::vector<std::filesystem::path> files;
	std::vector<Folder> folders;
};

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
	void renderFolder(Folder& folder);

private:
	ResourceManager& mResourceManager;

	Folder mAssetsFolder;
	bool mUpdateAssetsFolder;
	std::optional<std::filesystem::path> mSelectedPath;

	filewatch::FileWatch<std::string>* mAssetsWatcher;
};
}
