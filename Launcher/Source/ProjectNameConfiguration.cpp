#include "ProjectNameConfiguration.hpp"
#include "ProjectCreation.hpp"
#include "ApplicationCore/LetterChecker.hpp"
#include "ProjectPathConfiguration.hpp"

#include <imgui.h>

ProjectNameConfiguration::ProjectNameConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
	, m_error(ErrorVariation::noError)
	, m_previousError(ErrorVariation::noError)
	, m_errorText("")
	, m_bufferSize(256)
	, m_nameBuffer("MyProject")
{}

void ProjectNameConfiguration::update()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", m_nameBuffer, m_bufferSize))
	{
		updateErrorType();
		m_projectCreation.getPathConfiguration().updateErrorType();
	}
	if (m_error != ErrorVariation::noError)
	{
		if (m_error != m_previousError)
		{
			updateErrorText();
		}
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_errorText.c_str());
		ImGui::PopStyleColor();
	}
}

void ProjectNameConfiguration::reset()
{
	std::strncpy(m_nameBuffer, "MyProject", m_bufferSize);
	m_error = ErrorVariation::noError;
}

void ProjectNameConfiguration::updateErrorType()
{
	if (m_error != ErrorVariation::noError)
	{
		m_previousError = m_error;
	}
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
	if (fisrtLetter != '_' && !ApplicationCore::LetterChecker::isLatin(fisrtLetter))
	{
		if (!ApplicationCore::LetterChecker::isNumerical(fisrtLetter))
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
			!ApplicationCore::LetterChecker::isLatin(letter) &&
			!ApplicationCore::LetterChecker::isNumerical(letter))
		{
			m_error = ErrorVariation::unsupportedCharacter;
			return;
		}
	}
}

void ProjectNameConfiguration::updateErrorText()
{
	m_previousError = m_error;
	switch (m_error)
	{
	case ErrorVariation::empty:
		m_errorText = "Name is not writen";
		break;
	case ErrorVariation::firstLetter:
		m_errorText = "Name must start with latin symbol or '_'";
		break;
	case ErrorVariation::space:
		m_errorText = "Name cannot have spaces";
		break;
	case ErrorVariation::unsupportedCharacter:
		m_errorText = "Name must consist only of lating symbols, numbers and '_'";
		break;
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
