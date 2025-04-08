#pragma once
#include "File.hpp"

#include <vector>

namespace ProjectEditor::Window::AssetsBrowser
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
	std::vector<File>& getFiles();

	const std::filesystem::path& getPath() const;
	const std::vector<Folder>& getSubFolders() const;
	const std::vector<File>& getFiles() const;

private:
	std::filesystem::path mPath;
	std::vector<Folder> mSubFolders;
	std::vector<File> mFiles;
};
}
