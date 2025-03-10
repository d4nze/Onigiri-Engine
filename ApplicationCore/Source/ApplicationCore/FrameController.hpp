#pragma once
#include "Frame.hpp"

namespace ApplicationCore
{
class APPLICATION_CORE_API Application;

class APPLICATION_CORE_API FrameController
{
public:
	FrameController(Frame& mainFrame, Application& application);
	~FrameController();

public:
	void show();
	void setCurrentFrame(Frame* frame);

	Application& getApplication();
	const Application& getApplication() const;

private:
	Application& m_application;
	Frame* m_currentFrame;
};
}
