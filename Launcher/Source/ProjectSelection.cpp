#include "ProjectSelection.hpp"
#include "LauncherGUI.hpp"
#include "ProjectCreation.hpp"
#include "Application/BrowseWindow.hpp"
#include "LauncherApplication.hpp"

#include <imgui.h>

ProjectSelection::ProjectSelection(LauncherGUI& launcherGUI)
    : m_gui(launcherGUI)
    , m_projectsHolder()
{}

void ProjectSelection::update()
{
    if (ImGui::Button("New Project"))
    {
        m_gui.getStateManager().setState<ProjectCreation>();
    }
    ImGui::SameLine();
    if (ImGui::Button("Import Project"))
    {
        m_gui.getStateManager().setState<ProjectImporting>();
    }
    m_projectsHolder.update();
}

LauncherGUI& ProjectSelection::getGUI()
{
    return m_gui;
}

const LauncherGUI& ProjectSelection::getGUI() const
{
    return m_gui;
}

ProjectsHolder& ProjectSelection::getProjectsHolder()
{
    return m_projectsHolder;
}

const ProjectsHolder& ProjectSelection::getProjectsHolder() const
{
    return m_projectsHolder;
}
