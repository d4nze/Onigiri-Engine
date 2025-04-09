#pragma once
#include "ScopedStyle.hpp"

struct ImFont;
struct ImGuiIO;

namespace ApplicationCore::Font
{
class Manager
{
public:
	Manager(ImGuiIO& imGuiIO);

public:
	ScopedStyle createScopedStyle(Style fontStyle);

	void pushFontStyle(Style fontStyle);
	void popFontStyle();

private:
	ImFont* mMainFont;
	ImFont* mBoldFont;
	ImFont* mItalicFont;
	ImFont* mBoldItalicFont;
};
}
