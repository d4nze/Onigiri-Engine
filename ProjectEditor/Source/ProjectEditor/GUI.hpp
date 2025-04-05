#pragma once
#include "ApplicationCore/FrameController.hpp"

#include <imgui.h>
#include <map>
#include <typeindex>

namespace ProjectEditor
{
class Application;

namespace Window
{
class Window;
}

class GUI
{
public:
	GUI(Application& application);

public:
	void update();

	Application& getApplication();
	const Application& getApplication() const;

	template<class TWindow>
	TWindow* const getWindow();
	template<class TWindow>
	const TWindow* getWindow() const;

private:
	Window::Window* const getWindow(std::type_index typeID) const;

private:
	Application& mApplication;
	ImGuiIO& mImGuiIO;
	ImFont* mMainFont;
	std::map<std::type_index, Window::Window*> mWindows;
};
}

#include "GUI.inl"
