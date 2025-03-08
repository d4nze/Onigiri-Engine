#pragma once
class GUI;

class ProjectImporting
{
public:
	ProjectImporting(GUI& launcherGUI);

public:
	void update();
	void reset();

	GUI& getGUI();
	const GUI& getGUI() const;

private:
	GUI& m_gui;
};
