#include "ProjectImporting.hpp"

ProjectImporting::ProjectImporting(LauncherGUI& launcherGUI) : m_gui(launcherGUI) {}

void ProjectImporting::update() {}

void ProjectImporting::reset() {}

LauncherGUI& ProjectImporting::getGUI()
{
	return m_gui;
}

const LauncherGUI& ProjectImporting::getGUI() const
{
	return m_gui;
}
