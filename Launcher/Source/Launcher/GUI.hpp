#pragma once
#include "ApplicationCore/FrameController.hpp"
#include "ApplicationCore/GUI.hpp"

namespace Launcher
{
class Application;

class GUI : public ApplicationCore::GUI
{
public:
	GUI(Application& application);

public:
	void show() override;

	Application& getApplication();
	const Application& getApplication() const;

private:
	Application& mApplication;
	ApplicationCore::FrameController mFrameController;
};
}
