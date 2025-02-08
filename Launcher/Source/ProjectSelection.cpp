#include "ProjectSelection.hpp"
#include <imgui.h>

ProjectSelection::ProjectSelection() : m_projectsHolder() {}

void ProjectSelection::update()
{
    if (ImGui::Button("New Project"));
    ImGui::SameLine();
    if (ImGui::Button("Import Project"));
    m_projectsHolder.update();
}

ProjectsHolder& ProjectSelection::getProjectsHolder()
{
    return m_projectsHolder;
}

const ProjectsHolder& ProjectSelection::getProjectsHolder() const
{
    return m_projectsHolder;
}
