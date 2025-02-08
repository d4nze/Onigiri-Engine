#include "LauncherGUI.hpp"

LauncherGUI::LauncherGUI()
	: m_state(typeid(ProjectSelection))
	, m_projectSelection(*this)
	, m_projectCreation(*this)
{}

void LauncherGUI::update()
{
	if (m_state.is<ProjectSelection>())
	{
		m_projectSelection.update();
	}
	else if (m_state.is<ProjectCreation>())
	{
		m_projectCreation.update();
	}
}

LauncherState& LauncherGUI::getStateManager()
{
	return m_state;
}

const LauncherState& LauncherGUI::getStateManager() const
{
	return m_state;
}
