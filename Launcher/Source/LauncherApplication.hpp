#pragma once
#include "Application/Application.hpp"
#include "LauncherGUI.hpp"

#include <imgui.h>

class LauncherApplication : public Application
{
public:
	LauncherApplication();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	LauncherGUI m_gui;
};
