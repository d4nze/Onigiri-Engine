#include "FrameController.hpp"

#include <algorithm>
#include <vector>

ApplicationCore::FrameController::FrameController(Frame& mainFrame, Application& application)
	: m_application(application)
	, m_currentFrame(&mainFrame)
{}

ApplicationCore::FrameController::~FrameController()
{
	std::vector<Frame*> totalCollection = { m_currentFrame };
	std::vector<Frame*> selected = totalCollection;

	while (!selected.empty())
	{
		Frame* current = selected.front();
		for (std::pair<std::type_index, Frame*> neighbour : current->m_neighbours)
		{
			if (std::find(totalCollection.begin(), totalCollection.end(), neighbour.second) != totalCollection.end())
			{
				totalCollection.push_back(neighbour.second);
				selected.push_back(neighbour.second);
			}
		}
		selected.erase(selected.begin());
	}

	for (Frame* current : totalCollection)
	{
		delete current;
	}
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
