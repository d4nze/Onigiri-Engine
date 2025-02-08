#pragma once
#include "Application/Application.hpp"

class LauncherApplication : public Application
{
public:
	LauncherApplication();

private:
	void update() override;
};
