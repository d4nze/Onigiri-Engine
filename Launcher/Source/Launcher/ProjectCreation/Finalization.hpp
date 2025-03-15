#pragma once
#include "ApplicationCore/Frame.hpp"
#include "IStep.hpp"

namespace Launcher
{
namespace ProjectCreation
{
class Finalization : public ApplicationCore::Frame, public IStep
{
public:
	Finalization(ApplicationCore::FrameController& createController);

public:
	void show() override;
	bool hasError() override { return false; }
	bool moveBack() override;
	bool moveNext() override { return false; }
};
}
}
