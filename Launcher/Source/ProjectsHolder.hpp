#pragma once
#include "Project.hpp"
#include <vector>

class ProjectSelection;

class ProjectsHolder
{
public:
	ProjectsHolder(ProjectSelection& projectSelection);
	~ProjectsHolder();

public:
	void update();

	ProjectSelection& getProjectSelection();
	const ProjectSelection& getProjectSelection() const;

	std::vector<Project>::iterator begin();
	std::vector<Project>::iterator end();
	std::vector<Project>::const_iterator begin() const;
	std::vector<Project>::const_iterator end() const;

private:
	ProjectSelection& m_projectSelection;
	std::vector<Project> m_projects;
};
