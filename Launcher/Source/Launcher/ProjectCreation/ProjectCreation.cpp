#include "ProjectCreation.hpp"
#include "FileGeneration.hpp"
#include "Finalization.hpp"
#include "NameConfiguration.hpp"
#include "PathConfiguration.hpp"
#include "ApplicationCore/Application.hpp"
#include "ApplicationCore/FrameController.hpp"
#include "ProjectSelection/ProjectSelection.hpp"

#include <imgui.h>

Launcher::ProjectCreation::ProjectCreation::ProjectCreation(ApplicationCore::FrameController& frameController)
	: ApplicationCore::Frame(frameController)
	, mCreateController(frameController.getApplication())
	, mButtonWidth(80.f)
	, mCurrentStep(nullptr)
{
	Frame* nameConfiguration = mCreateController.addFrame<NameConfiguration>(new NameConfiguration(mCreateController));
	if (nameConfiguration == nullptr)
	{
		throw std::exception("Error creating NameConfiguration");
	}
	Frame* pathConfiguration = mCreateController.addFrame<PathConfiguration>(new PathConfiguration(mCreateController));
	if (pathConfiguration == nullptr)
	{
		throw std::exception("Error creating PathConfiguration");
	}
	Frame* finalization = mCreateController.addFrame<Finalization>(new Finalization(mCreateController));
	if (finalization == nullptr)
	{
		throw std::exception("Error creating Finalization");
	}

	mCreateController.setCurrentFrame<NameConfiguration>();
	mCurrentStep = dynamic_cast<IStep*>(mCreateController.getCurrentFrame());

	nameConfiguration->addNeighbour<PathConfiguration>();
	pathConfiguration->addNeighbour<NameConfiguration>();
	pathConfiguration->addNeighbour<Finalization>();
	finalization->addNeighbour<PathConfiguration>();
	finalization->addNeighbour<NameConfiguration>();
}

void Launcher::ProjectCreation::ProjectCreation::show()
{
	ImGui::BeginChild("Project List", ImVec2(0, ImGui::GetContentRegionAvail().y - 25), true);
	mCreateController.show();
	ImGui::EndChild();

	const float spacing = 10.f;
	const float windowWidth = ImGui::GetWindowWidth();
	const float totalButtonsWidth = mButtonWidth * 2.f + spacing;

	if (ImGui::Button("Cancel", ImVec2(mButtonWidth, 0)))
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
	bool disabled = mCreateController.isCurrentFrame<NameConfiguration>();
	if (disabled)
	{
		ImGui::BeginDisabled();
	}
	if (ImGui::Button("Back", ImVec2(mButtonWidth, 0)))
	{
		mCurrentStep->moveBack();
		mCurrentStep = dynamic_cast<IStep*>(mCreateController.getCurrentFrame());
	}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}

void Launcher::ProjectCreation::ProjectCreation::showNextButton()
{
	bool disabled = false;
	disabled = mCurrentStep->hasError();
	const char* m_nextButtonText = "Next";
	if (mCreateController.isCurrentFrame<Finalization>())
	{
		m_nextButtonText = "Finish";
	}
	if (disabled)
	{
		ImGui::BeginDisabled();
	}
	if (ImGui::Button(m_nextButtonText, ImVec2(mButtonWidth, 0)))
	{
		if (mCreateController.isCurrentFrame<Finalization>())
		{
			NameConfiguration* nameConfiguration = mCreateController.getFrame<NameConfiguration>();
			PathConfiguration* pathConfiguration = mCreateController.getFrame<PathConfiguration>();
			if (nameConfiguration != nullptr && pathConfiguration != nullptr)
			{
				FileGeneration fileGenerator(nameConfiguration->getName(), pathConfiguration->getPath());
				ProjectSelection::ProjectSelection* projectSelection = getController().getFrame<ProjectSelection::ProjectSelection>();
				if (projectSelection != nullptr)
				{
					ProjectSelection::ProjectsViewer& projectsViewer = projectSelection->getProjectsView();
					projectsViewer.push_back(new ProjectSelection::Project{ nameConfiguration->getName(), pathConfiguration->getPath() });
				}
				getController().getApplication().getWindow().close();
			}
		}
		if (mCurrentStep->moveNext())
		{
			mCurrentStep = dynamic_cast<IStep*>(mCreateController.getCurrentFrame());
		}
	}
	if (disabled)
	{
		ImGui::EndDisabled();
	}
}
