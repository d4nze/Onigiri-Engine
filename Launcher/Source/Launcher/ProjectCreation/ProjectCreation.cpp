#include "ProjectCreation.hpp"
#include "Finalization.hpp"
#include "NameConfiguration.hpp"
#include "PathConfiguration.hpp"
#include "ApplicationCore/Application.hpp"
#include "ApplicationCore/FrameController.hpp"
#include "ProjectSelection/ProjectSelection.hpp"

#include <imgui.h>

Launcher::ProjectCreation::ProjectCreation::ProjectCreation(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, m_createController(frameController.getApplication())
	, m_buttonWidth(80.f)
	, m_currentStep(nullptr)
{
	Frame* nameConfiguration = m_createController.addFrame<NameConfiguration>(new NameConfiguration(m_createController));
	if (nameConfiguration == nullptr)
	{
		throw std::exception("Error creating NameConfiguration");
	}
	Frame* pathConfiguration = m_createController.addFrame<PathConfiguration>(new PathConfiguration(m_createController));
	if (pathConfiguration == nullptr)
	{
		throw std::exception("Error creating PathConfiguration");
	}
	Frame* finalization = m_createController.addFrame<Finalization>(new Finalization(m_createController));
	if (finalization == nullptr)
	{
		throw std::exception("Error creating Finalization");
	}

	m_createController.setCurrentFrame<NameConfiguration>();
	m_currentStep = dynamic_cast<IStep*>(m_createController.getCurrentFrame());

	nameConfiguration->addNeighbour<PathConfiguration>();
	pathConfiguration->addNeighbour<NameConfiguration>();
	pathConfiguration->addNeighbour<Finalization>();
	finalization->addNeighbour<PathConfiguration>();
	finalization->addNeighbour<NameConfiguration>();
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
		moveToNeighbour<ProjectSelection::ProjectSelection>();
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
	if (ImGui::Button("Back", ImVec2(m_buttonWidth, 0)))
	{
		m_currentStep->moveBack();
		m_currentStep = dynamic_cast<IStep*>(m_createController.getCurrentFrame());
	}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}

void Launcher::ProjectCreation::ProjectCreation::showNextButton()
{
	bool disabled = false;
	disabled = m_currentStep->hasError();
	const char* m_nextButtonText = "Next";
	if (m_createController.isCurrentFrame<Finalization>())
	{
		m_nextButtonText = "Finish";
	}
	if (disabled)
	{
		ImGui::BeginDisabled();
	}
	if (ImGui::Button(m_nextButtonText, ImVec2(m_buttonWidth, 0)))
	{
		if (m_createController.isCurrentFrame<Finalization>())
		{
			// *Create project files*
			getController().getApplication().getWindow().close();
		}
		if (m_currentStep->moveNext())
		{
			m_currentStep = dynamic_cast<IStep*>(m_createController.getCurrentFrame());
		}
	}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}
