#pragma once
#include "ApplicationCore/GUI.hpp"
#include "Window/WindowHolder.hpp"
#include "MainMenuBar.hpp"

namespace ProjectEditor
{
class Application;

class GUI : public ApplicationCore::GUI
{
public:
	GUI(Application& application);

public:
	void show() override;

	Application& getApplication();
	Window::WindowHolder& getWindowHolder();

	const Application& getApplication() const;
	const Window::WindowHolder& getWindowHolder() const;

private:
	Application& mApplication;

	MainMenuBar mMainMenuBar;
	Window::WindowHolder mWindowHolder;
};
}
