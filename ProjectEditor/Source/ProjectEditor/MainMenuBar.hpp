#pragma once

namespace ProjectEditor
{
class GUI;

class MainMenuBar
{
public:
	MainMenuBar(GUI& gui);

public:
	void show();

	GUI& getGUI();
	const GUI& getGUI() const;

private:
	void showFileMenu();
	void showWindowMenu();
	void showHelpMenu();

private:
	GUI& mGUI;
};
}
