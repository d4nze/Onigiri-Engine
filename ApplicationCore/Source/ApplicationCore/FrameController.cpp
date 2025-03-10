#include "FrameController.hpp"

ApplicationCore::FrameController::FrameController(Frame& mainFrame, Application& application)
	: m_application(application)
	, m_currentFrame(&mainFrame)
{}

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

ApplicationCore::Application& ApplicationCore::FrameController::getApplication()
{
	return m_application;
}

const ApplicationCore::Application& ApplicationCore::FrameController::getApplication() const
{
	return m_application;
}
