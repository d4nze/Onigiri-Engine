#include "ResourceManager.hpp"

ProjectEditor::ResourceManager::ResourceManager(const std::filesystem::path& rootPath) : mRootPath(rootPath)
{}

const std::filesystem::path& ProjectEditor::ResourceManager::getRootPath() const
{
    return mRootPath;
}

std::filesystem::path ProjectEditor::ResourceManager::getResourcePath(const std::string& relativePath) const
{
	return mRootPath / relativePath;
}
