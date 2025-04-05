#include "GUI.hpp"

template<class TWindow>
inline TWindow* const ProjectEditor::GUI::getWindow()
{
	if (Window::Window* window = getWindow(typeid(TWindow)))
	{
		return reinterpret_cast<const TWindow*>(window);
	}
	return nullptr;
}

template<class TWindow>
inline const TWindow* ProjectEditor::GUI::getWindow() const
{
	if (Window::Window* window = getWindow(typeid(TWindow)))
	{
		return reinterpret_cast<const TWindow*>(window);
	}
	return nullptr;
}
