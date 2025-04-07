#include "WindowHolder.hpp"
#include <imgui.h>

ProjectEditor::Window::WindowHolder::WindowHolder(GUI& gui) : mAssetsBrowser(gui, true)
{}

void ProjectEditor::Window::WindowHolder::show()
{
    showWindow(mAssetsBrowser);
}

ProjectEditor::Window::AssetsBrowser& ProjectEditor::Window::WindowHolder::getAssetsBrowser()
{
    return mAssetsBrowser;
}

const ProjectEditor::Window::AssetsBrowser& ProjectEditor::Window::WindowHolder::getAssetsBrowser() const
{
    return mAssetsBrowser;
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
