#include "Inspector.hpp"
#include <imgui.h>

ProjectEditor::Window::Inspector::Inspector(GUI& gui, bool open)
	: Window(gui, "Inspector", open)
	, mInspectable(nullptr)
{}

void ProjectEditor::Window::Inspector::show()
{
	if (mInspectable == nullptr)
	{
		ImGui::Text("Select item to inspect");
		return;
	}
	mInspectable->inspect();
}

void ProjectEditor::Window::Inspector::setInspectable(Inspectable* inspectable)
{
	mInspectable = inspectable;
}

ProjectEditor::Window::Inspectable* ProjectEditor::Window::Inspector::getInspectable()
{
    return mInspectable;
}

const ProjectEditor::Window::Inspectable* ProjectEditor::Window::Inspector::getInspectable() const
{
	return mInspectable;
}
