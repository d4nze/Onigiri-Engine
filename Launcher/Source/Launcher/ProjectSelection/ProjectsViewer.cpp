#include "ProjectsViewer.hpp"
#include "ApplicationCore/Application.hpp"
#include "ApplicationCore/FrameController.hpp"
#include "ApplicationCore/MessageWindow.hpp"
#include "ProjectSelection.hpp"

#include <imgui.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

const char* Launcher::ProjectSelection::ProjectsViewer::m_saveFileName = "Project List.json";

Launcher::ProjectSelection::ProjectsViewer::ProjectsViewer(ProjectSelection& projectSelection)
	: m_projectSelection(projectSelection)
	, m_imGuiIO(ImGui::GetIO())
{
std::ifstream saveFile(m_saveFileName);
	if (saveFile.is_open())
	{
		nlohmann::json projectsData;
		saveFile >> projectsData;
		saveFile.close();

		for (const nlohmann::json& projectData : projectsData["projects"])
		{
			push_back(new Project{ projectData["name"], projectData["path"] });
		}
	}
}

Launcher::ProjectSelection::ProjectsViewer::~ProjectsViewer()
{
	std::ofstream file(m_saveFileName);
	if (file.is_open())
	{
		nlohmann::json projectsData;
		projectsData["projects"] = nlohmann::json::array();
		for (const Project* project : *this)
		{
			projectsData["projects"].push_back({ { "name", project->name }, { "path", project->path } });
		}
		file << projectsData.dump(4);
		file.close();
	}
}

void Launcher::ProjectSelection::ProjectsViewer::show()
{
	if (empty())
	{
		showEmpty();
	}
	else
	{
		showProjects();
	}
}

void Launcher::ProjectSelection::ProjectsViewer::showEmpty()
{
	ImVec2 childSize = ImGui::GetWindowSize();
	ImVec2 textSize = ImGui::CalcTextSize("No projects");
	ImVec2 textPos = ImVec2((childSize.x - textSize.x) / 2.f, (childSize.y - textSize.y) / 2.f);

	ImGui::SetCursorPos(textPos);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
	ImGui::TextUnformatted("No projects");
	ImGui::PopStyleColor();
}

void Launcher::ProjectSelection::ProjectsViewer::showProjects()
{
	ImGui::BeginChild("Project List", ImVec2(0, m_imGuiIO.DisplaySize.y - 40), true);
	for (std::vector<Project*>::iterator it = begin(); it != end(); it++)
	{
		Project* project = *it;
		ImGui::PushID(project);
		showProject(project);
		if (ImGui::BeginPopup(("ProjectMenuPopup")))
		{
			showProjectPopup(it);
		}
		ImGui::PopID();
	}
	ImGui::EndChild();
}

void Launcher::ProjectSelection::ProjectsViewer::showProject(Project* project)
{
	if (ImGui::Selectable("", false, ImGuiSelectableFlags_SpanAllColumns, ImVec2(0, 40)))
	{
		std::filesystem::path path = project->path + "\\" + project->name;
		if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
		{
			m_projectSelection.getController().getApplication().getWindow().close();
		}
		else
		{
			ApplicationCore::MessageWindow::show("Can't open project",
												 "No project in directory:\n" + project->path,
												 ApplicationCore::MessageWindow::Buttons::Ok,
												 ApplicationCore::MessageWindow::Icon::Error);
		}
	}
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
	{
		ImGui::OpenPopup(("ProjectMenuPopup"));
	}
	ImGui::SameLine();
	const float x = ImGui::GetCursorPosX();
	ImGui::TextUnformatted(project->name.c_str());
	ImGui::SetCursorPosX(x);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 20);
	ImGui::BeginDisabled();
	ImGui::TextUnformatted(project->path.c_str());
	ImGui::EndDisabled();
	ImGui::Separator();
}

void Launcher::ProjectSelection::ProjectsViewer::showProjectPopup(std::vector<Project*>::iterator& iterator)
{
	if (ImGui::MenuItem("Delete"))
	{
		Project* project = *iterator;
		std::filesystem::path path = project->path + "\\" + project->name;
		if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
		{
			std::filesystem::remove_all(path);
			delete* iterator;
			iterator = erase(iterator);
			ImGui::CloseCurrentPopup();
		}
		else
		{
			ApplicationCore::MessageWindow::show("Can't delete project",
												 "No project in directory:\n" + project->path,
												 ApplicationCore::MessageWindow::Buttons::Ok,
												 ApplicationCore::MessageWindow::Icon::Error);
		}
	}
	if (ImGui::MenuItem("Remove from list"))
	{
		delete* iterator;
		iterator = erase(iterator);
		ImGui::CloseCurrentPopup();
	}
	ImGui::EndPopup();
}
