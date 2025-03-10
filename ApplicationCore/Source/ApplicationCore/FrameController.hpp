#pragma once
#include "Frame.hpp"

namespace ApplicationCore
{
class APPLICATION_API FrameController
{
public:
	FrameController(Frame& mainFrame);
	~FrameController();

public:
	void show();
	void setCurrentFrame(Frame* frame);

private:
	Frame* m_currentFrame;
};
}
