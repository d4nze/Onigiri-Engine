#include "LauncherGUI.hpp"

LauncherGUI::LauncherGUI() : m_projectSelection(*this) {}

void LauncherGUI::update()
{
	m_projectSelection.update();
}
