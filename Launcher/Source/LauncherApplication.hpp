#pragma once
#include "Application/Application.hpp"
#include "Project.hpp"

#include <imgui.h>
#include <vector>

class LauncherApplication : public Application
{
public:
	LauncherApplication();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	std::vector<Project> m_projects;
};
