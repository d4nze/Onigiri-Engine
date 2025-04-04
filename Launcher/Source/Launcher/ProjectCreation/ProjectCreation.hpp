#pragma once
#include "ApplicationCore/FrameController.hpp"
#include "IStep.hpp"

#include <string>

namespace Launcher
{
namespace ProjectCreation
{
class ProjectCreation : public ApplicationCore::Frame
{
public:
	ProjectCreation(ApplicationCore::FrameController& frameController);

protected:
	void show() override;

private:
	void showBackButton();
	void showNextButton();

private:
	ApplicationCore::FrameController mCreateController;
	const float mButtonWidth;
	IStep* mCurrentStep;
};
}
}
