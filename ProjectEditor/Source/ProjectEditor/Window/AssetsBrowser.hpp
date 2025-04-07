#pragma once
#include "Inspectable.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"

#include <filesystem>
#include <vector>

namespace filewatch
{
template<class StringType>
class FileWatch;
}

namespace ProjectEditor::Window
{
class Folder;

class File : public Inspectable
{
public:
	File() = default;
	File(const std::filesystem::path& path);

public:
	void inspect() override;
	void show(Folder*& selectedFolder, File*& selectedFile);

	void setPath(const std::filesystem::path& path);
	std::filesystem::path& getPath();
	const std::filesystem::path& getPath() const;

private:
	std::filesystem::path mPath;
};

class Folder : public Inspectable
{
public:
	Folder() = default;
	Folder(const std::filesystem::path& path);

	void inspect() override;

	void show(Folder*& selectedFolder, File*& selectedFile);
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
	bool deselect() const;

private:
	ResourceManager& mResourceManager;

	Folder mAssetsFolder;
	bool mUpdateAssetsFolder;
	File* mSelectedFile;
	Folder* mSelectedFolder;

	filewatch::FileWatch<std::string>* mAssetsWatcher;
};
}
