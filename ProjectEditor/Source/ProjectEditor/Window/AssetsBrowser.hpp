#pragma once
#include "Window.hpp"
#include "ResourceManager.hpp"

namespace ProjectEditor::Window
{
class AssetsBrowser : public Window
{
public:
	AssetsBrowser(GUI& gui, bool open = false);

public:
	void show() override;

private:
	ResourceManager& mResourceManager;
};
}
