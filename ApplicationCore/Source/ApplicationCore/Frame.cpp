#include "Frame.hpp"
#include "FrameController.hpp"

ApplicationCore::Frame::Frame(FrameController& controller)
	: m_controller(controller)
	, m_parent({ nullptr, typeid(nullptr) })
{}

ApplicationCore::Frame::~Frame()
{
	for (std::pair<std::type_index, Frame*> neighbour : m_neighbours)
	{
		delete neighbour.second;
	}
}

bool ApplicationCore::Frame::moveUp()
{
	if (m_parent.first == nullptr)
	{
		return false;
	}
	m_controller.setCurrentFrame(m_parent.first);
	return true;
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

ApplicationCore::Frame* ApplicationCore::Frame::getParent(std::type_index frameIDType) const
{
	if (m_parent.second == frameIDType)
	{
		return m_parent.first;
	}
	return nullptr;
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

bool ApplicationCore::Frame::setParent(Frame* frame, std::type_index frameIDType)
{
	if (m_parent.first != nullptr)
	{
		return false;
	}
	m_parent.first = frame;
	m_parent.second = frameIDType;
	return true;
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
