#pragma once
#include "ProjectsHolder.hpp"

class LauncherGUI;

class ProjectSelection
{
public:
	ProjectSelection(LauncherGUI& launcherGUI);

public:
	void update();

	LauncherGUI& getGUI();
	const LauncherGUI& getGUI() const;

	ProjectsHolder& getProjectsHolder();
	const ProjectsHolder& getProjectsHolder() const;

private:
	LauncherGUI& m_gui;
	ProjectsHolder m_projectsHolder;
};
