#pragma once
#include "ApplicationCore/FrameController.hpp"
#include <imgui.h>

namespace Launcher
{
class Application;

class GUI
{
public:
	GUI(Application& application);

public:
	void update();

	Application& getApplication();
	const Application& getApplication() const;

private:
	Application& m_application;
	ImGuiIO& m_imGuiIO;
	ImFont* m_mainFont;
	ApplicationCore::Frame* m_mainFrame;
	ApplicationCore::FrameController m_frameController;
};
}
