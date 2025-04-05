#include "Window.hpp"

ProjectEditor::Window::Window::Window(GUI& gui, const char* title, bool open)
    : mGUI(gui)
    , mTitle(title)
    , mOpen(open)
{}

ProjectEditor::GUI& ProjectEditor::Window::Window::getGUI()
{
    return mGUI;
}

const ProjectEditor::GUI& ProjectEditor::Window::Window::getGUI() const
{
    return mGUI;
}

const char* ProjectEditor::Window::Window::getTitle()
{
    return mTitle;
}

bool ProjectEditor::Window::Window::isOpen() const
{
    return mOpen;
}

void ProjectEditor::Window::Window::setOpen(bool open)
{
    mOpen = open;
}

void ProjectEditor::Window::Window::open()
{
    mOpen = true;
}

void ProjectEditor::Window::Window::close()
{
	mOpen = false;
}
