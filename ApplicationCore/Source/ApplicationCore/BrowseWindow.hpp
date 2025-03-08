#pragma once
#include "ApplicationAPI.hpp"
#include <string>
#include <vector>
#include <filesystem>

namespace ApplicationCore
{
class BrowseWindow
{
public:
	static std::filesystem::path selectFolder();
};
}
