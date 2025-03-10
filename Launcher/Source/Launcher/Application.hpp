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
	GUI m_gui;
};
