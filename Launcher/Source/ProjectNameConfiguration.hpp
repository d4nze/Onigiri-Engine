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
	const std::string getName() const;

	bool hasError() const;

private:
	class ErrorVariation
	{
	public:
		static const char* noError;
		static const char* empty;
		static const char* firstLetter;
		static const char* space;
		static const char* unsupportedCharacter;
	};

private:
	ProjectCreation& m_projectCreation;
	std::string m_error;
	const std::int32_t m_bufferSize;
	char m_nameBuffer[256];
};
