#pragma once
#include <string>

namespace Launcher
{
namespace ProjectCreation
{
class FileGeneration
{
public:
	FileGeneration(std::string name, std::string path);

private:
	bool generateFolders();
	bool generateRootFolder();
	bool generateAssetsFolder();
	bool generateScriptFolders();

	bool generateFiles();
	bool generateProjectFile();
	bool generateSceneFile();
	bool generatePremakeFiles();

private:
	std::string mName;
	std::string mPath;
	std::string mRootPath;
	std::string mScriptsPath;
	std::string mMainScriptsPath;
	std::string mInspectorScriptsPath;
	std::string mEditorScriptsPath;
};
}
}
