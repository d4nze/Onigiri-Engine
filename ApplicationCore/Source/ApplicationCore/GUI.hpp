#pragma once
#include "Font/Manager.hpp"

namespace ApplicationCore
{
class Application;

class GUI
{
public:
	GUI();
	virtual ~GUI() = default;

public:
	virtual void show() = 0;

	Font::Manager& getFontManager();
	const Font::Manager& getFontManager() const;

protected:
	ImGuiIO& mImGuiIO;

private:
	Font::Manager mFontManager;
};
}
