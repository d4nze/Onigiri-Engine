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
	if (hasNeighbour(neighbourTypeID))
	{
		m_controller.m_currentFrame = m_controller.m_frames.at(neighbourTypeID);
		return true;
	}
	return false;
}

bool ApplicationCore::Frame::addNeighbour(std::type_index neighbourTypeID)
{
	if (hasNeighbour(neighbourTypeID))
	{
		return false;
	}
	m_controller.m_connections.insert({ *m_controller.m_typeIDs.at(const_cast<Frame*>(this)), neighbourTypeID });
	return true;
}

bool ApplicationCore::Frame::hasNeighbour(std::type_index neighbourTypeID) const
{
	std::type_index myTypeID = *m_controller.m_typeIDs.at(const_cast<Frame*>(this));
	return m_controller.m_connections.find({ myTypeID, neighbourTypeID }) != m_controller.m_connections.end();
}

ApplicationCore::Frame* ApplicationCore::Frame::getNeighbour(std::type_index neighbourTypeID) const
{
	if (hasNeighbour(neighbourTypeID))
	{
		return m_controller.m_frames.at(neighbourTypeID);
	}
	return nullptr;
}
