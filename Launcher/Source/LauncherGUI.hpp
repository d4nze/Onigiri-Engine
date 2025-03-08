#pragma once
#include "LauncherState.hpp"
#include <imgui.h>

class Application;

class LauncherGUI
{
public:
	LauncherGUI(Application& application);

public:
	void update();

	Application& getApplication();
	const Application& getApplication() const;

	LauncherState& getStateManager();
	const LauncherState& getStateManager() const;

	ProjectSelection& getProjectSelection();
	const ProjectSelection& getProjectSelection() const;

	ProjectCreation& getProjectCreation();
	const ProjectCreation& getProjectCreation() const;

private:
	Application& m_application;
	LauncherState m_state;
	ProjectSelection m_projectSelection;
	ProjectCreation m_projectCreation;
	ProjectImporting m_projectImporting;
	ImFont* m_mainFont;
};
