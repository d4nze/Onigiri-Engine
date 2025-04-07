#pragma once

namespace ProjectEditor
{
class GUI;
namespace Window
{
class Window
{
public:
	Window(GUI& gui, const char* title, bool open = false);
	virtual ~Window() = default;

public:
	virtual void show() = 0;

	GUI& getGUI();
	const GUI& getGUI() const;

	const char* getTitle();

	bool isOpen() const;
	void setOpen(bool open);
	void open();
	void close();

private:
	GUI& mGUI;
	const char* mTitle;
	bool mOpen;

	friend class WindowHolder;
};
}
}
