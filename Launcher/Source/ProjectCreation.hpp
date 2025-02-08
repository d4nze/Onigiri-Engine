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

	ProjectCreationStep& getStepManager();

private:
	LauncherGUI& m_launcherGUI;
	ProjectCreationStep m_step;
	ProjectNameConfiguration m_nameConfiguration;
};
