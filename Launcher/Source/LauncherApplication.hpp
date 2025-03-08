#pragma once
#include "ApplicationCore/Application.hpp"
#include "LauncherGUI.hpp"

#include <imgui.h>

class LauncherApplication : public ApplicationCore::Application
{
public:
	LauncherApplication();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	LauncherGUI m_gui;
};
