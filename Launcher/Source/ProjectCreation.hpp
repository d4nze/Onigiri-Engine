#pragma once
#include "ProjectCreationStep.hpp"

class LauncherGUI;

class ProjectCreation
{
public:
	ProjectCreation(LauncherGUI& launcherGUI);

public:
	void update();
	void reset();

	LauncherGUI& getGUI();
	const LauncherGUI& getGUI() const;

private:
	LauncherGUI& m_gui;
	ProjectCreationStep m_step;
	ProjectNameConfiguration m_nameConfiguration;
	ProjectPathConfiguration m_pathConfiguration;
};
