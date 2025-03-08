#pragma once
#include "ProjectCreationStep.hpp"

class GUI;

class ProjectCreation
{
public:
	ProjectCreation(GUI& launcherGUI);

public:
	void update();
	void reset();

	GUI& getGUI();
	const GUI& getGUI() const;

	ProjectNameConfiguration& getNameConfiguration();
	ProjectPathConfiguration& getPathConfiguration();
	const ProjectNameConfiguration& getNameConfiguration() const;
	const ProjectPathConfiguration& getPathConfiguration() const;

private:
	GUI& m_gui;
	ProjectCreationStep m_step;
	ProjectNameConfiguration m_nameConfiguration;
	ProjectPathConfiguration m_pathConfiguration;
};
