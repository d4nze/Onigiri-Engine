#include "Frame.hpp"
#include "FrameController.hpp"

ApplicationCore::Frame::Frame(FrameController& controller) : m_controller(controller)
{}

ApplicationCore::Frame::~Frame()
{
	for (std::pair<std::type_index, Frame*> neighbour : m_neighbours)
	{
		delete neighbour.second;
	}
}

ApplicationCore::FrameController& ApplicationCore::Frame::getController()
{
	return m_controller;
}

const ApplicationCore::FrameController& ApplicationCore::Frame::getController() const
{
	return m_controller;
}

bool ApplicationCore::Frame::moveDown(std::type_index frameIDType)
{
	if (m_neighbours.find(frameIDType) == m_neighbours.end())
	{
		return false;
	}
	m_controller.setCurrentFrame(m_neighbours[frameIDType]);
	return true;
}

ApplicationCore::Frame* ApplicationCore::Frame::getNeighbour(std::type_index frameIDType)
{
	if (m_neighbours.find(frameIDType) == m_neighbours.end())
	{
		return nullptr;
	}
	return m_neighbours[frameIDType];
}

const ApplicationCore::Frame* ApplicationCore::Frame::getNeighbour(std::type_index frameIDType) const
{
	if (m_neighbours.find(frameIDType) == m_neighbours.end())
	{
		return nullptr;
	}
	return m_neighbours.at(frameIDType);
}

bool ApplicationCore::Frame::addNeighbour(Frame* frame, std::type_index frameIDType)
{
	if (m_neighbours.find(frameIDType) != m_neighbours.end())
	{
		return false;
	}
	m_neighbours[frameIDType] = frame;
	return true;
}
