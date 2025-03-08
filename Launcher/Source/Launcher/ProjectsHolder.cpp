#include "ProjectsHolder.hpp"
#include <imgui.h>
#include <fstream>
#include <nlohmann/json.hpp>

ProjectsHolder::ProjectsHolder(ProjectSelection& projectSelection) : m_projectSelection(projectSelection)
{
	std::ifstream file("Project List.json");
	if (file.is_open())
	{
		nlohmann::json projectsData;
		file >> projectsData;
		file.close();

		for (const nlohmann::json& projectData : projectsData["projects"])
		{
			m_projects.push_back(Project(*this, projectData["name"], projectData["path"]));
		}
	}
}

ProjectsHolder::~ProjectsHolder()
{
	std::ofstream file("Project List.json");
	if (file.is_open())
	{
		nlohmann::json projectsData;
		projectsData["projects"] = nlohmann::json::array();
		for (const Project& project : m_projects)
		{
			projectsData["projects"].push_back({ { "name", project.getName() }, { "path", project.getPath() } });
		}
		file << projectsData.dump(4);
		file.close();
	}
}

void ProjectsHolder::update()
{
	if (m_projects.empty())
	{
		ImVec2 childSize = ImGui::GetWindowSize();
		ImVec2 textSize = ImGui::CalcTextSize("No projects");
		ImVec2 textPos = ImVec2((childSize.x - textSize.x) / 2.f, (childSize.y - textSize.y) / 2.f);

		ImGui::SetCursorPos(textPos);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
		ImGui::TextUnformatted("No projects");
		ImGui::PopStyleColor();
		return;
	}

	static ImGuiIO& io = ImGui::GetIO();
	ImGui::BeginChild("Project List", ImVec2(0, io.DisplaySize.y - 40), true);
	for (std::size_t i = 0; i < m_projects.size(); i++)
	{
		ImGui::PushID(i);
		m_projects[i].update();
		if (ImGui::BeginPopup(("ProjectMenuPopup")))
		{
			if (ImGui::MenuItem("Delete"))
			{
				// add delete folder functional
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Remove from list"))
			{
				m_projects.erase(m_projects.begin() + i);
				i--;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}
	ImGui::EndChild();
}

ProjectSelection& ProjectsHolder::getProjectSelection()
{
	return m_projectSelection;
}

const ProjectSelection& ProjectsHolder::getProjectSelection() const
{
	return m_projectSelection;
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
