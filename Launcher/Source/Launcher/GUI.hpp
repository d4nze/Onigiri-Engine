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
	Application& mApplication;
	ImGuiIO& mImGuiIO;
	ImFont* mMainFont;
	ApplicationCore::FrameController mFrameController;
};
}
