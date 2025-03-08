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

	std::string getName();
	std::string getPath();
	const std::string getName() const;
	const std::string getPath() const;

private:
	LauncherGUI& m_gui;
	ProjectCreationStep m_step;
	ProjectNameConfiguration m_nameConfiguration;
	ProjectPathConfiguration m_pathConfiguration;
};
