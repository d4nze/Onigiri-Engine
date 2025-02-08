#pragma once
#include "Application/Application.hpp"
#include "ProjectSelection.hpp"

#include <imgui.h>

class LauncherApplication : public Application
{
public:
	LauncherApplication();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	ProjectSelection m_projectSelection;
};
