#pragma once
#include <string>

class ProjectsHolder;

class Project
{
public:
	Project();
	Project(ProjectsHolder& holder, const std::string& name, const std::string& path);

public:
	void update();

	void setName(const std::string& name);
	void setPath(const std::string& path);
	const std::string& getName() const;
	const std::string& getPath() const;

private:
	ProjectsHolder* m_holder;
	std::string m_name;
	std::string m_path;
};
