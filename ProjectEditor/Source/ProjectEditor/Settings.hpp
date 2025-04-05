#pragma once
#include <filesystem>

namespace ProjectEditor
{
class Settings
{
public:
	Settings();
	~Settings();

public:
	std::filesystem::path getCurrentProjectPath() const;

private:
	std::filesystem::path mCurrentProjectPath;
};
}
