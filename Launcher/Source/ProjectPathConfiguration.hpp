#pragma once
#include <string>

class ProjectCreation;

class ProjectPathConfiguration
{
public:
	ProjectPathConfiguration(ProjectCreation& projectCreation);

public:
	void update();
	void reset();
	void updateErrorLog();

	std::string getPath();
	bool hasError() const;

private:
	class ErrorVariation
	{
	public:
		static const char* noError;
		static const char* empty;
		static const char* relativePath;
		static const char* projectExists;
		static const char* invalidPath;
	};

private:
	ProjectCreation& m_projectCreation;
	std::string m_error;
	const std::int32_t m_bufferSize;
	char m_pathBuffer[256];
};
