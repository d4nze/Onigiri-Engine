#include "ScopedStyle.hpp"
#include "Manager.hpp"

ApplicationCore::Font::ScopedStyle::~ScopedStyle()
{
	mFontManager.popFontStyle();
}

ApplicationCore::Font::ScopedStyle::ScopedStyle(Manager& manager, Style fontStyle) : mFontManager(manager)
{
	mFontManager.pushFontStyle(fontStyle);
}
