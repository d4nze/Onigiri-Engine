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
	void updateErrorType();
	void updateErrorText();

	std::string getPath();
	const std::string getPath() const;

	bool hasError() const;

private:
	enum class ErrorVariation
	{
		noError,
		empty,
		relativePath,
		projectExists,
		invalidPath
	};

private:
	ProjectCreation& m_projectCreation;
	ErrorVariation m_error;
	ErrorVariation m_previousError;
	std::string m_errorText;
	const std::int32_t m_bufferSize;
	char m_pathBuffer[256];
};
