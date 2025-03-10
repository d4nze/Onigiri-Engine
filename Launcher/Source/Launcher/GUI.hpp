#pragma once
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
};
}
