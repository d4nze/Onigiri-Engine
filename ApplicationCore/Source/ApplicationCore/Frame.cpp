#include "Frame.hpp"
#include "FrameController.hpp"

ApplicationCore::Frame::Frame(FrameController& controller) : m_controller(controller)
{}

ApplicationCore::FrameController& ApplicationCore::Frame::getController()
{
	return m_controller;
}

const ApplicationCore::FrameController& ApplicationCore::Frame::getController() const
{
	return m_controller;
}

bool ApplicationCore::Frame::moveToNeighbour(std::type_index neighbourTypeID)
{
	if (m_neighbours.find(neighbourTypeID) == m_neighbours.end())
	{
		return false;
	}
	m_controller.m_currentFrame = m_controller.m_frames.at(neighbourTypeID);
	return true;
}
