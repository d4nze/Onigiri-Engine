#pragma once
#include "ApplicationCore/Application.hpp"
#include "LauncherGUI.hpp"

#include <imgui.h>

class Application : public ApplicationCore::Application
{
public:
	Application();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	LauncherGUI m_gui;
};
