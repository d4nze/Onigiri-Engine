#pragma once
#include "ApplicationCore/FrameController.hpp"
#include <string>

namespace Launcher
{
class ProjectCreation : public ApplicationCore::Frame
{
public:
	ProjectCreation(ApplicationCore::FrameController& frameController);

protected:
	void show() override;
};
}
