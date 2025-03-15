#pragma once
#include "ApplicationCore/FrameController.hpp"
#include "ProjectsViewer.hpp"

namespace Launcher
{
class ProjectSelection : public ApplicationCore::Frame
{
public:
	ProjectSelection(ApplicationCore::FrameController& frameController);

public:
	ProjectsViewer& getProjectsView();
	const ProjectsViewer& getProjectsView() const;

protected:
	void show() override;

private:
	ProjectsViewer m_projectsViewer;
};
}
