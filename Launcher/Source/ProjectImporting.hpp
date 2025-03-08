#pragma once
class LauncherGUI;

class ProjectImporting
{
public:
	ProjectImporting(LauncherGUI& launcherGUI);

public:
	void update();
	void reset();

	LauncherGUI& getGUI();
	const LauncherGUI& getGUI() const;

private:
	LauncherGUI& m_gui;
};
