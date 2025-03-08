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
	void updateErrorType();
	void updateErrorText();

	std::string getName();
	const std::string getName() const;

	bool hasError() const;

private:
	enum class ErrorVariation
	{
		noError,
		empty,
		firstLetter,
		space,
		unsupportedCharacter
	};

private:
	ProjectCreation& m_projectCreation;
	ErrorVariation m_error;
	ErrorVariation m_previousError;
	std::string m_errorText;
	const std::int32_t m_bufferSize;
	char m_nameBuffer[256];
};
