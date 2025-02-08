#include "ProjectsHolder.hpp"
#include <imgui.h>

ProjectsHolder::ProjectsHolder()
{
	m_projects = {
		{ "Project Alpha",  "C:/Projects/Alpha" },
		{ "Project Beta",   "C:/Projects/Beta" },
		{ "Project Gamma",  "C:/Projects/Gamma" },
	};
}

void ProjectsHolder::update()
{
	static ImGuiIO& io = ImGui::GetIO();
	ImGui::BeginChild("Project List", ImVec2(0, io.DisplaySize.y - 50), true);
	for (std::size_t i = 0; i < m_projects.size(); i++)
	{
		ImGui::PushID(i);
		m_projects[i].update();
		ImGui::PopID();
	}
	ImGui::EndChild();
}

std::vector<Project>::iterator ProjectsHolder::begin()
{
	return m_projects.begin();
}

std::vector<Project>::iterator ProjectsHolder::end()
{
	return m_projects.end();
}

std::vector<Project>::const_iterator ProjectsHolder::begin() const
{
	return m_projects.begin();
}

std::vector<Project>::const_iterator ProjectsHolder::end() const
{
	return m_projects.end();
}
