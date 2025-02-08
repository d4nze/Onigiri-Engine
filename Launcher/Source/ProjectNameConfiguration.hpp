#pragma once
#include <string>

class ProjectCreation;

class ProjectNameConfiguration
{
public:
	ProjectNameConfiguration(ProjectCreation& projectCreation);

public:
	void update();
	void reset();

	std::string getName();

private:
	ProjectCreation& m_projectCreation;
	const std::int32_t m_bufferSize;
	char m_nameBuffer[256];
};
