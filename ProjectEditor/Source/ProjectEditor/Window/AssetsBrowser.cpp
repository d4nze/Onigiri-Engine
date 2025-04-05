#include "AssetsBrowser.hpp"

#include <filesystem>

ProjectEditor::Window::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
{}

void ProjectEditor::Window::AssetsBrowser::show()
{
	if (ImGui::TreeNodeEx("Assets", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::TreePop();
	}
}
