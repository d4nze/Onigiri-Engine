#include "NameConfiguration.hpp"
#include "PathConfiguration.hpp"
#include "ApplicationCore/LetterChecker.hpp"

#include <imgui.h>

Launcher::ProjectCreation::NameConfiguration::NameConfiguration(ApplicationCore::FrameController& createController)
    : ApplicationCore::Frame(createController)
    , m_bufferSize(255)
    , m_name(m_bufferSize, '\0')
    , m_errorType(ErrorType::NoError)
	, m_previousErrorType(m_errorType)
	, m_errorText("")
{
	updateErrorType();
}

void Launcher::ProjectCreation::NameConfiguration::reset()
{
    m_name = std::string(m_bufferSize, '\0');
	m_errorType = ErrorType::NoError;
	m_previousErrorType = m_errorType;
}

void Launcher::ProjectCreation::NameConfiguration::updateErrorType()
{
	if (m_errorType != ErrorType::NoError)
	{
		m_previousErrorType = m_errorType;
	}
	m_errorType = ErrorType::NoError;
	const char fisrtLetter = m_name[0];
	if (fisrtLetter == '\0')
	{
		m_errorType = ErrorType::Empty;
		return;
	}
	if (fisrtLetter == ' ')
	{
		m_errorType = ErrorType::Space;
		return;
	}
	if (fisrtLetter != '_' && !ApplicationCore::LetterChecker::isLatin(fisrtLetter))
	{
		if (!ApplicationCore::LetterChecker::isNumerical(fisrtLetter))
		{
			m_errorType = ErrorType::UnsupportedCharacter;
			return;
		}
		m_errorType = ErrorType::FirstLetter;
		return;
	}
	for (std::int32_t i = 0; i < m_bufferSize; i++)
	{
		const char letter = m_name[i];
		if (letter == '\0')
		{
			return;
		}
		if (letter == ' ')
		{
			m_errorType = ErrorType::Space;
			return;
		}
		if (letter != '_' &&
			!ApplicationCore::LetterChecker::isLatin(letter) &&
			!ApplicationCore::LetterChecker::isNumerical(letter))
		{
			m_errorType = ErrorType::UnsupportedCharacter;
			return;
		}
	}
}

bool Launcher::ProjectCreation::NameConfiguration::hasError()
{
	return m_errorType != ErrorType::NoError;
}

bool Launcher::ProjectCreation::NameConfiguration::moveNext()
{
	return moveToNeighbour<PathConfiguration>();
}

std::string Launcher::ProjectCreation::NameConfiguration::getName() const
{
    return m_name.c_str();
}

Launcher::ProjectCreation::NameConfiguration::ErrorType Launcher::ProjectCreation::NameConfiguration::getError() const
{
    return m_errorType;
}

void Launcher::ProjectCreation::NameConfiguration::show()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", m_name.data(), m_bufferSize))
	{
		updateErrorType();
		if (PathConfiguration* pathConfiguration = getNeighbour<PathConfiguration>())
		{
			pathConfiguration->updateErrorType();
		}
	}
	if (m_errorType != ErrorType::NoError)
	{
		if (m_errorType != m_previousErrorType)
		{
			m_previousErrorType = m_errorType;
			updateErrorText();
		}
		showError();
	}
}

void Launcher::ProjectCreation::NameConfiguration::showError()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
	ImGui::Text(m_errorText.c_str());
	ImGui::PopStyleColor();
}

void Launcher::ProjectCreation::NameConfiguration::updateErrorText()
{
	switch (m_errorType)
	{
	case ErrorType::Empty:
		m_errorText = "Name is not writen";
		break;
	case ErrorType::FirstLetter:
		m_errorText = "Name must start with latin symbol or '_'";
		break;
	case ErrorType::Space:
		m_errorText = "Name cannot have spaces";
		break;
	case ErrorType::UnsupportedCharacter:
		m_errorText = "Name must consist only of lating symbols, numbers and '_'";
		break;
	}
}
