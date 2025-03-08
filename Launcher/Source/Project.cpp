#include "Project.hpp"
#include "Application/MessageWindow.hpp"
#include "ProjectsHolder.hpp"
#include "ProjectSelection.hpp"
#include "LauncherGUI.hpp"
#include "LauncherApplication.hpp"

#include <filesystem>
#include <imgui.h>

Project::Project()
    : m_holder(nullptr)
    , m_name("")
    , m_path("")
{}

Project::Project(ProjectsHolder& holder, const std::string& name, const std::string& path)
	: m_holder(&holder)
    , m_name(name)
	, m_path(path)
{}

void Project::update()
{
    if (ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns, ImVec2(0, 40)))
    {
        std::filesystem::path path = m_path + "\\" + m_name;
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
        {
            m_holder->getProjectSelection().getGUI().getApplication().getWindow().close();
        }
        else
        {
            MessageWindow::PressedButton result = MessageWindow::show("Can't open project",
                                                                      "No project in directory:\n" + m_path,
                                                                      MessageWindow::Buttons::Ok,
                                                                      MessageWindow::Icon::Error);
        }
    }
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
        ImGui::OpenPopup(("ProjectMenuPopup"));
    }
    ImGui::SameLine();
    const float x = ImGui::GetCursorPosX();
    ImGui::TextUnformatted(m_name.c_str());
    ImGui::SetCursorPosX(x);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 20);
    ImGui::BeginDisabled();
    ImGui::TextUnformatted(m_path.c_str());
    ImGui::EndDisabled();
    ImGui::Separator();
}

void Project::setName(const std::string& name)
{
    m_name = name;
}

void Project::setPath(const std::string& path)
{
    m_path = path;
}

const std::string& Project::getName() const
{
    return m_name;
}

const std::string& Project::getPath() const
{
    return m_path;
}
