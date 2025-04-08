#include "WindowHolder.hpp"
#include <imgui.h>

ProjectEditor::Window::WindowHolder::WindowHolder(GUI& gui)
    : mAssetsBrowser(gui, true)
    , mInspector(gui, true)
{}

void ProjectEditor::Window::WindowHolder::show()
{
    showWindow(mAssetsBrowser);
    showWindow(mInspector);
}

ProjectEditor::Window::AssetsBrowser::AssetsBrowser& ProjectEditor::Window::WindowHolder::getAssetsBrowser()
{
    return mAssetsBrowser;
}

const ProjectEditor::Window::AssetsBrowser::AssetsBrowser& ProjectEditor::Window::WindowHolder::getAssetsBrowser() const
{
    return mAssetsBrowser;
}

ProjectEditor::Window::Inspector& ProjectEditor::Window::WindowHolder::getInspector()
{
    return mInspector;
}

const ProjectEditor::Window::Inspector& ProjectEditor::Window::WindowHolder::getInspector() const
{
    return mInspector;
}

void ProjectEditor::Window::WindowHolder::showWindow(Window& window)
{
    if (!window.isOpen() || !ImGui::Begin(window.getTitle(), &window.mOpen))
    {
        return;
    }
    window.show();
    ImGui::End();
}
