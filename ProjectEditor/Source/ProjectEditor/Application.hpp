#pragma once
#include "ApplicationCore/Application.hpp"
#include "GUI.hpp"
#include "ResourceManager.hpp"
#include "Settings.hpp"

#include <imgui.h>

namespace ProjectEditor
{
class Application : public ApplicationCore::Application
{
public:
	Application();

public:
	Settings& getSettings();
	const Settings& getSettings() const;

	ResourceManager& getResourceManager();
	const ResourceManager& getResourceManager() const;

	GUI& getGUI();
	const GUI& getGUI() const;

private:
	void update() override;

private:
	Settings mSettings;
	ResourceManager mResourceManager;
	GUI mGUI;
};
}
