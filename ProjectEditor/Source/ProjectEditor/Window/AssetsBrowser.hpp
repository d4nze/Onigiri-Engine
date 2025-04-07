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
class Folder
{
public:
	Folder() = default;
	Folder(const std::filesystem::path& path);

	void show(std::optional<std::filesystem::path>& selectedPath);
	void clear();

	void setPath(const std::filesystem::path& path);
	Folder& addSubFolder(const std::filesystem::path& subFolderPath);
	void addFilePath(const std::filesystem::path& filePath);

	std::filesystem::path& getPath();
	std::vector<Folder>& getSubFolders();
	std::vector<std::filesystem::path>& getFilePaths();

	const std::filesystem::path& getPath() const;
	const std::vector<Folder>& getSubFolders() const;
	const std::vector<std::filesystem::path>& getFilePaths() const;

private:
	std::filesystem::path mPath;
	std::vector<Folder> mSubFolders;
	std::vector<std::filesystem::path> mFilePaths;
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
	bool deselect() const;

private:
	ResourceManager& mResourceManager;

	Folder mAssetsFolder;
	bool mUpdateAssetsFolder;
	std::optional<std::filesystem::path> mSelectedPath;

	filewatch::FileWatch<std::string>* mAssetsWatcher;
};
}
