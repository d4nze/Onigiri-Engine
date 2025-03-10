#include "FrameController.hpp"

ApplicationCore::FrameController::FrameController(Frame& mainFrame) : m_currentFrame(&mainFrame) {}

ApplicationCore::FrameController::~FrameController()
{
	Frame* parent = m_currentFrame;
	for (; parent->m_parent.first != nullptr; parent = parent->m_parent.first);
	delete parent;
}

void ApplicationCore::FrameController::show()
{
	m_currentFrame->show();
}

void ApplicationCore::FrameController::setCurrentFrame(Frame* frame)
{
	if (frame == nullptr)
	{
		return;
	}
	m_currentFrame = frame;
}
