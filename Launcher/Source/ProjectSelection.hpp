#pragma once
#include "ProjectsHolder.hpp"

class GUI;

class ProjectSelection
{
public:
	ProjectSelection(GUI& launcherGUI);

public:
	void update();

	GUI& getGUI();
	const GUI& getGUI() const;

	ProjectsHolder& getProjectsHolder();
	const ProjectsHolder& getProjectsHolder() const;

private:
	GUI& m_gui;
	ProjectsHolder m_projectsHolder;
};
