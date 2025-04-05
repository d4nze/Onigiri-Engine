#pragma once
#include "Window.hpp"

namespace ProjectEditor::Window
{
class AssetsBrowser : public Window
{
public:
	AssetsBrowser(GUI& gui, bool open = false);

public:
	void show() override;
};
}
