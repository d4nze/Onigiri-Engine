#include "Project.hpp"
#include <imgui.h>

Project::Project(const std::string& name, const std::string& path)
	: m_name(name)
	, m_path(path)
{}

void Project::Update()
{
    if (ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns, ImVec2(0, 40)));
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
