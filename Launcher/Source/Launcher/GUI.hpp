#pragma once
#include "GUIState.hpp"
#include <imgui.h>

class Application;

class GUI
{
public:
	GUI(Application& application);

public:
	void update();

	Application& getApplication();
	const Application& getApplication() const;

	GUIState& getStateManager();
	const GUIState& getStateManager() const;

	ProjectSelection& getProjectSelection();
	const ProjectSelection& getProjectSelection() const;

	ProjectCreation& getProjectCreation();
	const ProjectCreation& getProjectCreation() const;

private:
	Application& m_application;
	GUIState m_state;
	ProjectSelection m_projectSelection;
	ProjectCreation m_projectCreation;
	ProjectImporting m_projectImporting;
	ImFont* m_mainFont;
};
