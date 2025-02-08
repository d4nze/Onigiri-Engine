#include "LauncherGUI.hpp"

LauncherGUI::LauncherGUI()
	: m_projectSelection(*this)
	, m_projectCreation(*this)
{}

void LauncherGUI::update()
{
	m_projectSelection.update();
}
