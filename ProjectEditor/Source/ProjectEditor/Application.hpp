#pragma once
#include "ApplicationCore/Application.hpp"
#include "GUI.hpp"
#include "Settings.hpp"

#include <imgui.h>

namespace ProjectEditor
{
class Application : public ApplicationCore::Application
{
public:
	Application();

private:
	void update() override;

	Settings& getSettings();
	const Settings& getSettings() const;

	GUI& getGUI();
	const GUI& getGUI() const;

private:
	Settings mSettings;
	GUI mGUI;
};
}
