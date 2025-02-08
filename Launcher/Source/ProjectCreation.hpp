#pragma once
#include "ProjectNameConfiguration.hpp"

class LauncherGUI;

class ProjectCreation
{
public:
	ProjectCreation(LauncherGUI& launcherGUI);

public:
	void update();
	void reset();

private:
	LauncherGUI& m_launcherGUI;
	ProjectNameConfiguration m_nameConfiguration;
};
