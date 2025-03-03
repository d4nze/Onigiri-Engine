#pragma once
#include "ProjectsHolder.hpp"

class LauncherGUI;

class ProjectSelection
{
public:
	ProjectSelection(LauncherGUI& launcherGUI);

public:
	void update();

	ProjectsHolder& getProjectsHolder();
	const ProjectsHolder& getProjectsHolder() const;

private:
	LauncherGUI& m_gui;
	ProjectsHolder m_projectsHolder;
};
