#pragma once
#include "ApplicationCore/FrameController.hpp"
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
	ApplicationCore::FrameController m_createController;
	const float m_buttonWidth;
};
}
}
