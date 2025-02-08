#pragma once
#include "ProjectsHolder.hpp"

class LauncherGUI;

class ProjectCreation
{
public:
	ProjectCreation(LauncherGUI& launcherGUI);

public:
	void update();

private:
	LauncherGUI& m_launcherGUI;
};
