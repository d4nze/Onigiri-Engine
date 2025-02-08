#pragma once
#include "ProjectsHolder.hpp"

class ProjectSelection
{
public:
	ProjectSelection();

public:
	void update();

	ProjectsHolder& getProjectsHolder();
	const ProjectsHolder& getProjectsHolder() const;

private:
	ProjectsHolder m_projectsHolder;
};
