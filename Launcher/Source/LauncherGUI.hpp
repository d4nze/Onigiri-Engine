#pragma once
#include "ProjectSelection.hpp"
#include "ProjectCreation.hpp"

class LauncherGUI
{
public:
	LauncherGUI();

public:
	void update();

private:
	ProjectSelection m_projectSelection;
	ProjectCreation m_projectCreation;
};
