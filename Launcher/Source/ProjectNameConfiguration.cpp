#include "ProjectNameConfiguration.hpp"
#include "ProjectCreation.hpp"
#include "Application/LetterChecker.hpp"

#include <imgui.h>

const char* ProjectNameConfiguration::ErrorVariation::noError = "";
const char* ProjectNameConfiguration::ErrorVariation::empty = "Name is not writen";
const char* ProjectNameConfiguration::ErrorVariation::firstLetter = "Name must start with latin symbol or '_'";
const char* ProjectNameConfiguration::ErrorVariation::space = "Name cannot have spaces";
const char* ProjectNameConfiguration::ErrorVariation::unsupportedCharacter = "Name must consist only of lating symbols, numbers and '_'";

ProjectNameConfiguration::ProjectNameConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_error(ErrorVariation::noError)
	, m_bufferSize(256)
	, m_nameBuffer("MyProject")
{}

void ProjectNameConfiguration::update()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", m_nameBuffer, m_bufferSize))
	{
		updateErrorLog();
	}
	if (m_error != ErrorVariation::noError)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_error.c_str());
		ImGui::PopStyleColor();
	}
}

void ProjectNameConfiguration::reset()
{
	std::strncpy(m_nameBuffer, "MyProject", m_bufferSize);
	m_error = ErrorVariation::noError;
}

void ProjectNameConfiguration::updateErrorLog()
{
	m_error = ErrorVariation::noError;
	const char fisrtLetter = m_nameBuffer[0];
	if (fisrtLetter == '\0')
	{
		m_error = ErrorVariation::empty;
		return;
	}
	if (fisrtLetter == ' ')
	{
		m_error = ErrorVariation::space;
		return;
	}
	if (fisrtLetter != '_' && !LetterChecker::isLatin(fisrtLetter))
	{
		if (!LetterChecker::isNumerical(fisrtLetter))
		{
			m_error = ErrorVariation::unsupportedCharacter;
			return;
		}
		m_error = ErrorVariation::firstLetter;
		return;
	}
	for (std::int32_t i = 0; i < m_bufferSize; i++)
	{
		const char letter = m_nameBuffer[i];
		if (letter == '\0')
		{
			return;
		}
		if (letter == ' ')
		{
			m_error = ErrorVariation::space;
			return;
		}
		if (letter != '_' &&
			!LetterChecker::isLatin(letter) &&
			!LetterChecker::isNumerical(letter))
		{
			m_error = ErrorVariation::unsupportedCharacter;
			return;
		}
	}
}

std::string ProjectNameConfiguration::getName()
{
	return std::string(m_nameBuffer);
}

const std::string ProjectNameConfiguration::getName() const
{
	return std::string(m_nameBuffer);
}

bool ProjectNameConfiguration::hasError() const
{
	return m_error != ErrorVariation::noError;
}
