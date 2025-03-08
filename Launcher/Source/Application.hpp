#pragma once
#include "ApplicationCore/Application.hpp"
#include "GUI.hpp"

#include <imgui.h>

class Application : public ApplicationCore::Application
{
public:
	Application();

private:
	void update() override;

private:
	ImGuiIO& m_imGuiIO;
	GUI m_gui;
};
