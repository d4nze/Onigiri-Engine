#pragma once
#include "Window/WindowHolder.hpp"
#include "MainMenuBar.hpp"

#include <map>
#include <typeindex>

struct ImGuiIO;
struct ImFont;

namespace ProjectEditor
{
class Application;

class GUI
{
public:
	GUI(Application& application);

public:
	void show();

	Application& getApplication();
	Window::WindowHolder& getWindowHolder();

	const Application& getApplication() const;
	const Window::WindowHolder& getWindowHolder() const;

private:
	void initializeFont();

private:
	Application& mApplication;

	ImGuiIO& mImGuiIO;
	ImFont* mMainFont;

	MainMenuBar mMainMenuBar;
	Window::WindowHolder mWindowHolder;
};
}
