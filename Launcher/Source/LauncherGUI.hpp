#pragma once
#include "LauncherState.hpp"

class LauncherGUI
{
public:
	LauncherGUI();

public:
	void update();

	LauncherState& getStateManager();
	const LauncherState& getStateManager() const;

private:
	LauncherState m_state;
	ProjectSelection m_projectSelection;
	ProjectCreation m_projectCreation;
};
