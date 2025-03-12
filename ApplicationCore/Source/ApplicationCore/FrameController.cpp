#include "FrameController.hpp"

#include <algorithm>
#include <vector>

ApplicationCore::FrameController::FrameController(Application& application)
	: m_application(application)
	, m_currentFrame(nullptr)
{}

ApplicationCore::FrameController::~FrameController()
{
	for (std::pair<std::type_index, Frame*> frameHolder : m_frames)
	{
		delete frameHolder.second;
	}
}

void ApplicationCore::FrameController::show()
{
	if (m_currentFrame != nullptr)
	{
		m_currentFrame->show();
	}
}

ApplicationCore::Frame* ApplicationCore::FrameController::getCurrentFrame()
{
	return m_currentFrame;
}

const ApplicationCore::Frame* ApplicationCore::FrameController::getCurrentFrame() const
{
	return m_currentFrame;
}

ApplicationCore::Application& ApplicationCore::FrameController::getApplication()
{
	return m_application;
}

const ApplicationCore::Application& ApplicationCore::FrameController::getApplication() const
{
	return m_application;
}

bool ApplicationCore::FrameController::setCurrentFrame(std::type_index frameTypeID)
{
	if (hasFrame(frameTypeID))
	{
		m_currentFrame = m_frames.at(frameTypeID);
		return true;
	}
	return false;
}

bool ApplicationCore::FrameController::isCurrentFrame(std::type_index frameTypeID) const
{
	std::map<std::type_index, Frame*>::const_iterator it = m_frames.find(frameTypeID);
	if (it == m_frames.end())
	{
		return false;
	}
	return it->second == m_currentFrame;
}

ApplicationCore::Frame* ApplicationCore::FrameController::addFrame(Frame* frame, std::type_index frameTypeID)
{
	if (hasFrame(frameTypeID))
	{
		delete frame;
		return nullptr;
	}
	m_frames[frameTypeID] = frame;
	return frame;
}

bool ApplicationCore::FrameController::hasFrame(std::type_index frameTypeID) const
{
	return m_frames.find(frameTypeID) != m_frames.end();
}

ApplicationCore::Frame* ApplicationCore::FrameController::getFrame(std::type_index frameTypeID) const
{
	if (hasFrame(frameTypeID))
	{
		return m_frames.at(frameTypeID);
	}
	return nullptr;
}

bool ApplicationCore::FrameController::addNeighbour(Frame* frame, std::type_index neighbourTypeID)
{
	if (hasNeighbour(frame, neighbourTypeID))
	{
		return false;
	}
	frame->m_neighbours.insert(neighbourTypeID);
	return true;
}

bool ApplicationCore::FrameController::hasNeighbour(Frame* frame, std::type_index neighbourTypeID) const
{
	if (m_frames.find(neighbourTypeID) == m_frames.end())
	{
		return false;
	}
	for (std::pair<std::type_index, Frame*> frameHolder : m_frames)
	{
		if (frameHolder.second == frame)
		{
			return true;
		}
	}
	return false;
}

ApplicationCore::Frame* ApplicationCore::FrameController::getNeighbour(Frame* frame, std::type_index neighbourTypeID) const
{
	if (hasNeighbour(frame, neighbourTypeID))
	{
		if (frame->m_neighbours.find(neighbourTypeID) != frame->m_neighbours.end())
		{
			return m_frames.at(neighbourTypeID);
		}
		return nullptr;
	}
	return nullptr;
}
