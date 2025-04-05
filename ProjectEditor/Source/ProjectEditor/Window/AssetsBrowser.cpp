#include "AssetsBrowser.hpp"
#include "Application.hpp"

#include <filesystem>

ProjectEditor::Window::AssetsBrowser::AssetsBrowser(GUI& gui, bool open)
	: Window(gui, "Assets Browser", open)
	, mResourceManager(gui.getApplication().getResourceManager())
{}

void ProjectEditor::Window::AssetsBrowser::show()
{
	if (ImGui::TreeNodeEx("Assets", ImGuiTreeNodeFlags_DefaultOpen))
	{
		std::filesystem::path assetsPath = mResourceManager.getRootPath() / "Assets";
		for (const auto& entry : std::filesystem::directory_iterator(assetsPath))
		{
			// ...
		}
		ImGui::TreePop();
	}
}
