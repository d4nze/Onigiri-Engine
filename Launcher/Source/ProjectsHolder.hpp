#pragma once
#include "Project.hpp"
#include <vector>

class ProjectsHolder
{
public:
	ProjectsHolder();

public:
	void update();

	std::vector<Project>::iterator begin();
	std::vector<Project>::iterator end();
	std::vector<Project>::const_iterator begin() const;
	std::vector<Project>::const_iterator end() const;

private:
	std::vector<Project> m_projects;
};
