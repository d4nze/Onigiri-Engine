#include "ProjectCreation.hpp"
#include "LauncherGUI.hpp"
#include "ProjectSelection.hpp"
#include "Application.hpp"

#include <imgui.h>

ProjectCreation::ProjectCreation(LauncherGUI& launcherGUI)
    : m_gui(launcherGUI)
    , m_step(typeid(ProjectNameConfiguration))
    , m_nameConfiguration(*this)
    , m_pathConfiguration(*this)
{}

void ProjectCreation::update()
{
    ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
    if (m_step.is<ProjectNameConfiguration>())
    {
        m_nameConfiguration.update();
    }
    else if (m_step.is<ProjectPathConfiguration>())
    {
        m_pathConfiguration.update();
    }
    ImGui::EndChild();

    float buttonWidth = 80.0f;
    float spacing = 10.0f;
    float windowWidth = ImGui::GetWindowWidth();
    float totalButtonsWidth = buttonWidth * 2 + spacing;

    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
    {
        m_gui.getStateManager().setState<ProjectSelection>();
        reset();
    }

    bool isDisabled = m_step.is<ProjectNameConfiguration>();
    ImGui::SameLine(windowWidth - totalButtonsWidth - ImGui::GetStyle().ItemSpacing.x);
    if (isDisabled)
    {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Back", ImVec2(buttonWidth, 0)))
    {
        if (m_step.is<ProjectPathConfiguration>())
        {
            m_step.setStep<ProjectNameConfiguration>();
        }
    }
    if (isDisabled)
    {
        ImGui::EndDisabled();
    }

    ImGui::SameLine();
    const char* nextStepText = "Next";
    bool nextStepDisabled = false;
    if (m_step.is<ProjectPathConfiguration>())
    {
        nextStepText = "Finish";
        nextStepDisabled = m_pathConfiguration.hasError();
    }
    else
    {
        nextStepDisabled = m_nameConfiguration.hasError();
    }
    if (nextStepDisabled)
    {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button(nextStepText, ImVec2(buttonWidth, 0)))
    {
        if (m_step.is<ProjectNameConfiguration>())
        {
            m_nameConfiguration.updateErrorType();
            if (!m_nameConfiguration.hasError())
            {
                m_step.setStep<ProjectPathConfiguration>();
            }
        }
        else
        {
            m_pathConfiguration.updateErrorType();
            if (!m_pathConfiguration.hasError())
            {
                m_gui.getApplication().getWindow().close();
            }
        }
    }
    if (nextStepDisabled)
    {
        ImGui::EndDisabled();
    }
}

void ProjectCreation::reset()
{
    m_step.setStep<ProjectNameConfiguration>();
    m_nameConfiguration.reset();
    m_pathConfiguration.reset();
}

LauncherGUI& ProjectCreation::getGUI()
{
    return m_gui;
}

const LauncherGUI& ProjectCreation::getGUI() const
{
    return m_gui;
}

ProjectNameConfiguration& ProjectCreation::getNameConfiguration()
{
    return m_nameConfiguration;
}

ProjectPathConfiguration& ProjectCreation::getPathConfiguration()
{
    return m_pathConfiguration;
}

const ProjectNameConfiguration& ProjectCreation::getNameConfiguration() const
{
    return m_nameConfiguration;
}

const ProjectPathConfiguration& ProjectCreation::getPathConfiguration() const
{
    return m_pathConfiguration;
}
