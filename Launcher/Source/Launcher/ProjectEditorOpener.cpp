#include "ProjectEditorOpener.hpp"
#include "ProjectSelection/ProjectsViewer.hpp"

#include <filesystem>

Launcher::ProjectEditorOpener::ProjectEditorOpener(const ProjectSelection::Project& selectedProject)
{
	if (std::filesystem::exists("ProjectEditorSettings.json"))
	{
		if (!openReader())
		{
			return;
		}
		mSettingsReader >> mSettings;
		mSettingsReader.close();
	}

	updateProject(selectedProject);

	if (!openWriter())
	{
		return;
	}
	mSettingsWriter << std::setw(4) << mSettings;
	mSettingsWriter.close();

	std::system("ProjectEditor.exe");
}

bool Launcher::ProjectEditorOpener::openReader()
{
	mSettingsReader.open("ProjectEditorSettings.json");
	return mSettingsReader.is_open() && mSettingsReader.good();
}

void Launcher::ProjectEditorOpener::updateProject(const ProjectSelection::Project& selectedProject)
{
	std::filesystem::path fullPath(selectedProject.path);
	fullPath /= selectedProject.name;
	mSettings["Current Project"] = fullPath.string();
}

bool Launcher::ProjectEditorOpener::openWriter()
{
	mSettingsWriter.open("ProjectEditorSettings.json");
	return mSettingsWriter.is_open() && mSettingsWriter.good();
}
