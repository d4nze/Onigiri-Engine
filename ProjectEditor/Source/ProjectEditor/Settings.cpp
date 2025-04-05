#include "Settings.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

ProjectEditor::Settings::Settings()
{
	std::ifstream settingsFile("Project Editor Settings.json");
	nlohmann::json settingsData;
	if (!settingsFile.is_open() || !settingsFile.good())
	{
		return;
	}
	settingsFile >> settingsData;
	settingsFile.close();

	mCurrentProjectPath = settingsData["Current Project"].get<std::string>();
}

ProjectEditor::Settings::~Settings()
{
	std::ofstream settingsFile("Project Editor Settings.json");
	nlohmann::json settingsData;
	if (!settingsFile.is_open() || !settingsFile.good())
	{
		return;
	}
	settingsData["Current Project"] = mCurrentProjectPath.string();
	settingsFile << std::setw(4) << settingsData;
	settingsFile.close();
}

std::filesystem::path ProjectEditor::Settings::getCurrentProjectPath() const
{
    return mCurrentProjectPath;
}
