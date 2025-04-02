#include "FileGeneration.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

Launcher::ProjectCreation::FileGeneration::FileGeneration(std::string name, std::string path)
    : m_name(name)
    , m_path(path)
    , m_rootPath(path + '\\' + name + '\\')
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
    return std::filesystem::create_directory(m_rootPath);
}

bool Launcher::ProjectCreation::FileGeneration::generateAssetsFolder()
{
    return std::filesystem::create_directory(m_rootPath + "Assets");
}

bool Launcher::ProjectCreation::FileGeneration::generateScriptFolders()
{
    m_scriptsPath = m_rootPath + "Scripts\\";
    m_mainScriptsPath = m_scriptsPath + "Main\\";
    m_inspectorScriptsPath = m_scriptsPath + "Inspector\\";
    m_editorScriptsPath = m_scriptsPath + "Editor\\";

    return std::filesystem::create_directory(m_scriptsPath)
        && std::filesystem::create_directory(m_mainScriptsPath)
        && std::filesystem::create_directory(m_inspectorScriptsPath)
        && std::filesystem::create_directory(m_editorScriptsPath);
}

bool Launcher::ProjectCreation::FileGeneration::generateFiles()
{
    return generateProjectFile()
        && generateSceneFile()
        && generatePremakeFiles();
}

bool Launcher::ProjectCreation::FileGeneration::generateProjectFile()
{
    std::ofstream projectFile(m_rootPath + m_name + ".json");
    if (!projectFile.is_open())
    {
        return false;
    }
    nlohmann::json projectData;
    projectData["Name"] = m_name;
    projectData["Author"] = "Unknown";
    projectData["StartScene"] = "Scene";
    projectFile << std::setw(4) << projectData;
    projectFile.close();
    return true;
}

bool Launcher::ProjectCreation::FileGeneration::generateSceneFile()
{
    std::ofstream sceneFile(m_rootPath + "Scene.json");
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
    std::ofstream scriptsPremakeFile(m_scriptsPath + "premake5.lua");
    if (!scriptsPremakeFile.is_open())
    {
        return false;
    }
    scriptsPremakeFile.close();
    std::ofstream mainPremakeFile(m_mainScriptsPath + "premake5.lua");
    if (!mainPremakeFile.is_open())
    {
        return false;
    }
    mainPremakeFile.close();
    std::ofstream inspectorPremakeFile(m_inspectorScriptsPath + "premake5.lua");
    if (!inspectorPremakeFile.is_open())
    {
        return false;
    }
    inspectorPremakeFile.close();
    std::ofstream editorPremakeFile(m_editorScriptsPath + "premake5.lua");
    if (!editorPremakeFile.is_open())
    {
        return false;
    }
    editorPremakeFile.close();
    return true;
}
