#pragma once
#include "ApplicationAPI.hpp"
#include <string>
#include <vector>
#include <filesystem>

class BrowseWindow
{
public:
	static std::filesystem::path selectFolder();
};
