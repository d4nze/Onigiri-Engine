#include "ProjectCreation.hpp"
#include "NameConfiguration.hpp"
#include "../ProjectSelection.hpp"

#include <imgui.h>

Launcher::ProjectCreation::ProjectCreation::ProjectCreation(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, m_createController(frameController.getApplication())
	, m_buttonWidth(80.f)
{
	frameController.addNeighbour<ProjectSelection>(this);
	if (m_createController.addFrame<NameConfiguration>(new NameConfiguration(m_createController)) != nullptr)
	{
		m_createController.setCurrentFrame<NameConfiguration>();
	}
}

void Launcher::ProjectCreation::ProjectCreation::show()
{
	ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
	m_createController.show();
	ImGui::EndChild();

	const float spacing = 10.f;
	const float windowWidth = ImGui::GetWindowWidth();
	const float totalButtonsWidth = m_buttonWidth * 2.f + spacing;

	if (ImGui::Button("Cancel", ImVec2(m_buttonWidth, 0)))
	{
		moveToNeighbour<ProjectSelection>();
	}
	ImGui::SameLine(windowWidth - totalButtonsWidth - ImGui::GetStyle().ItemSpacing.x);
	showBackButton();
	ImGui::SameLine();
	showNextButton();
}

void Launcher::ProjectCreation::ProjectCreation::showBackButton()
{
	bool disabled = m_createController.isCurrentFrame<NameConfiguration>();
	if (disabled)
	{
		ImGui::BeginDisabled();
	}
	if (ImGui::Button("Back", ImVec2(m_buttonWidth, 0))) {}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}

void Launcher::ProjectCreation::ProjectCreation::showNextButton()
{
	bool disabled = false;
	if (IStep* currentStep = dynamic_cast<IStep*>(m_createController.getCurrentFrame()))
	{
		disabled = currentStep->hasError();
	}
	const char* m_nextButtonText = "Next";
	if (m_createController.isCurrentFrame<NameConfiguration>()) // Change later
	{
		m_nextButtonText = "Finish";
	}
	if (disabled)
	{
		ImGui::BeginDisabled();
	}
	if (ImGui::Button(m_nextButtonText, ImVec2(m_buttonWidth, 0))) {}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}
