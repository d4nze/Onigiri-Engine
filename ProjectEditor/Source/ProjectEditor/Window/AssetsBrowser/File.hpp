#pragma once
#include <filesystem>
#include <optional>

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
}
