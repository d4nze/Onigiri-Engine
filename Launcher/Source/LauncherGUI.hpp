#pragma once
#include "ProjectSelection.hpp"

class LauncherGUI
{
public:
	LauncherGUI();

public:
	void update();

private:
	ProjectSelection m_projectSelection;
};
