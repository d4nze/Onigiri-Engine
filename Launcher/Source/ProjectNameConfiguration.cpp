#include "ProjectNameConfiguration.hpp"
#include "ProjectCreation.hpp"
#include "Application/LetterChecker.hpp"

#include <imgui.h>

ProjectNameConfiguration::ProjectNameConfiguration(ProjectCreation& projectCreation)
	: m_projectCreation(projectCreation)
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
	if (!m_error.empty())
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
		ImGui::Text(m_error.c_str());
		ImGui::PopStyleColor();
	}
}

void ProjectNameConfiguration::reset()
{
	std::strncpy(m_nameBuffer, "MyProject", m_bufferSize);
}

void ProjectNameConfiguration::updateErrorLog()
{
	m_error = "";
	const char fisrtLetter = m_nameBuffer[0];
	if (fisrtLetter == '\0')
	{
		m_error = "Name is not writen";
		return;
	}
	if (fisrtLetter != '_' && !LetterChecker::isLatin(fisrtLetter))
	{
		if (!LetterChecker::isNumerical(fisrtLetter))
		{
			m_error = "Name must consist only of lating symbols, numbers and '_'";
			return;
		}
		m_error = "Name must start with latin symbol or '_'";
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
			m_error = "Name cannot have spaces";
			return;
		}
		if (letter != '_' &&
			!LetterChecker::isLatin(letter) &&
			!LetterChecker::isNumerical(letter))
		{
			m_error = "Name must consist only of lating symbols, numbers and '_'";
			return;
		}
	}
}

std::string ProjectNameConfiguration::getName()
{
	return std::string(m_nameBuffer);
}
