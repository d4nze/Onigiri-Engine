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
	std::string m_name;
	std::string m_path;
	std::string m_rootPath;
	std::string m_scriptsPath;
	std::string m_mainScriptsPath;
	std::string m_inspectorScriptsPath;
	std::string m_editorScriptsPath;
};
}
}
