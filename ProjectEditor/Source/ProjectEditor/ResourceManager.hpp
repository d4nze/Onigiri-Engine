#pragma once
#include <filesystem>

namespace ProjectEditor
{
class ResourceManager
{
public:
	ResourceManager(const std::filesystem::path& rootPath);

public:
	const std::filesystem::path& getRootPath() const;
	std::filesystem::path getResourcePath(const std::string& relativePath) const;

private:
	std::filesystem::path mRootPath;
};
}
