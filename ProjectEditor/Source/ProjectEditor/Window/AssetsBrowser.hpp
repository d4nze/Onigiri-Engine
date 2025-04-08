#pragma once
#include "Inspectable.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"

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
class Folder;

class File
{
public:
	File() = default;
	File(const std::filesystem::path& path);

public:
	void show(std::optional<std::filesystem::path>& selectedPath);

	void setPath(const std::filesystem::path& path);
	std::filesystem::path& getPath();
	const std::filesystem::path& getPath() const;

private:
	std::filesystem::path mPath;
};

class InspectableFile : public Inspectable, public File
{
public:
	InspectableFile();

public:
	void update();
	void inspect() override;

private:
	std::optional<std::string> mErrorText;
	std::string mName;
	std::string mExtension;
	float mSize;
};

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
	std::vector<File>& getFiles();

	const std::filesystem::path& getPath() const;
	const std::vector<Folder>& getSubFolders() const;
	const std::vector<File>& getFiles() const;

private:
	std::filesystem::path mPath;
	std::vector<Folder> mSubFolders;
	std::vector<File> mFiles;
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
