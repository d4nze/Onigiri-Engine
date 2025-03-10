#pragma once
#include <imgui.h>

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
	ImFont* m_mainFont;
};
