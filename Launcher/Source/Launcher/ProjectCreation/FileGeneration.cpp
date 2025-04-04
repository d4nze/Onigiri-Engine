#include "FileGeneration.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

Launcher::ProjectCreation::FileGeneration::FileGeneration(std::string name, std::string path)
    : mName(name)
    , mPath(path)
    , mRootPath(path + '\\' + name + '\\')
{
    if (!generateFolders())
    {
        throw std::exception("Error generating folders");
    }
    if (!generateFiles())
    {
        throw std::exception("Error generating files");
    }
}

bool Launcher::ProjectCreation::FileGeneration::generateFolders()
{
    return generateRootFolder()
        && generateAssetsFolder()
        && generateScriptFolders();
}

bool Launcher::ProjectCreation::FileGeneration::generateRootFolder()
{
    return std::filesystem::create_directory(mRootPath);
}

bool Launcher::ProjectCreation::FileGeneration::generateAssetsFolder()
{
    return std::filesystem::create_directory(mRootPath + "Assets");
}

bool Launcher::ProjectCreation::FileGeneration::generateScriptFolders()
{
    mScriptsPath = mRootPath + "Scripts\\";
    mMainScriptsPath = mScriptsPath + "Main\\";
    mInspectorScriptsPath = mScriptsPath + "Inspector\\";
    mEditorScriptsPath = mScriptsPath + "Editor\\";

    return std::filesystem::create_directory(mScriptsPath)
        && std::filesystem::create_directory(mMainScriptsPath)
        && std::filesystem::create_directory(mInspectorScriptsPath)
        && std::filesystem::create_directory(mEditorScriptsPath);
}

bool Launcher::ProjectCreation::FileGeneration::generateFiles()
{
    return generateProjectFile()
        && generateSceneFile()
        && generatePremakeFiles();
}

bool Launcher::ProjectCreation::FileGeneration::generateProjectFile()
{
    std::ofstream projectFile(mRootPath + mName + ".json");
    if (!projectFile.is_open())
    {
        return false;
    }
    nlohmann::json projectData;
    projectData["Name"] = mName;
    projectData["Author"] = "Unknown";
    projectData["StartScene"] = "Scene";
    projectFile << std::setw(4) << projectData;
    projectFile.close();
    return true;
}

bool Launcher::ProjectCreation::FileGeneration::generateSceneFile()
{
    std::ofstream sceneFile(mRootPath + "Scene.json");
    if (!sceneFile.is_open())
    {
        return false;
    }
    nlohmann::json sceneData;
    sceneData["Instances"] = nlohmann::json::array();
    sceneFile << std::setw(4) << sceneData;
    sceneFile.close();
    return true;
}

bool Launcher::ProjectCreation::FileGeneration::generatePremakeFiles()
{
    std::ofstream scriptsPremakeFile(mScriptsPath + "premake5.lua");
    if (!scriptsPremakeFile.is_open())
    {
        return false;
    }
    scriptsPremakeFile.close();
    std::ofstream mainPremakeFile(mMainScriptsPath + "premake5.lua");
    if (!mainPremakeFile.is_open())
    {
        return false;
    }
    mainPremakeFile.close();
    std::ofstream inspectorPremakeFile(mInspectorScriptsPath + "premake5.lua");
    if (!inspectorPremakeFile.is_open())
    {
        return false;
    }
    inspectorPremakeFile.close();
    std::ofstream editorPremakeFile(mEditorScriptsPath + "premake5.lua");
    if (!editorPremakeFile.is_open())
    {
        return false;
    }
    editorPremakeFile.close();
    return true;
}
