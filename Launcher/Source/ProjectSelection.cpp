#include "ProjectSelection.hpp"
#include "GUI.hpp"
#include "ProjectCreation.hpp"
#include "ApplicationCore/BrowseWindow.hpp"
#include "Application.hpp"

#include <imgui.h>

ProjectSelection::ProjectSelection(GUI& launcherGUI)
    : m_gui(launcherGUI)
    , m_projectsHolder(*this)
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

GUI& ProjectSelection::getGUI()
{
    return m_gui;
}

const GUI& ProjectSelection::getGUI() const
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
