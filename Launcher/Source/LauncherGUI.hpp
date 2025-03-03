#pragma once
#include "LauncherState.hpp"
#include <imgui.h>

class LauncherApplication;

class LauncherGUI
{
public:
	LauncherGUI(LauncherApplication& application);

public:
	void update();

	LauncherApplication& getApplication();
	const LauncherApplication& getApplication() const;

	LauncherState& getStateManager();
	const LauncherState& getStateManager() const;

	ProjectSelection& getProjectSelection();
	const ProjectSelection& getProjectSelection() const;

	ProjectCreation& getProjectCreation();
	const ProjectCreation& getProjectCreation() const;

private:
	LauncherApplication& m_application;
	LauncherState m_state;
	ProjectSelection m_projectSelection;
	ProjectCreation m_projectCreation;
	ImFont* m_mainFont;
};
