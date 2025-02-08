#pragma once
#include "Application/Application.hpp"
#include "ProjectsHolder.hpp"

#include <imgui.h>

class LauncherApplication : public Application
{
public:
	LauncherApplication();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	ProjectsHolder m_projectsHolder;
};
