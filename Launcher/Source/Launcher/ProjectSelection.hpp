#pragma once
#include "ApplicationCore/FrameController.hpp"

namespace Launcher
{
class ProjectSelection : public ApplicationCore::Frame
{
public:
	ProjectSelection(ApplicationCore::FrameController& frameController);

protected:
	void show() override;
};
}
