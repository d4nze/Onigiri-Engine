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
	void updateErrorLog();

	std::string getName();
	bool hasError() const;

private:
	ProjectCreation& m_projectCreation;
	std::string m_error;
	const std::int32_t m_bufferSize;
	char m_nameBuffer[256];
};
