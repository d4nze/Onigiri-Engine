#pragma once
#include <imgui.h>
#include <string>
#include <vector>

namespace Launcher
{
namespace ProjectSelection
{
class ProjectSelection;

struct Project
{
	std::string name;
	std::string path;
};

class ProjectsViewer : public std::vector<Project*>
{
public:
	ProjectsViewer(ProjectSelection& projectSelection);
	~ProjectsViewer();

public:
	void show();

private:
	void showEmpty();
	void showProjects();
	void showProject(Project* project);
	void showProjectPopup(std::vector<Project*>::iterator& iterator);

private:
	ProjectSelection& m_projectSelection;
	ImGuiIO& m_imGuiIO;
	static const char* m_saveFileName;
};
}
}
