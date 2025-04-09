#pragma once

namespace ApplicationCore::Font
{
enum class Style
{
	Normal,
	Bold,
	Italic,
	BoldItalic
};

class Manager;

class ScopedStyle
{
public:
	~ScopedStyle();

private:
	ScopedStyle(Manager& manager, Style fontStyle);

	ScopedStyle() = delete;
	ScopedStyle(const ScopedStyle&) = delete;
	ScopedStyle& operator=(const ScopedStyle&) = delete;
	ScopedStyle(ScopedStyle&&) = delete;

private:
	Manager& mFontManager;

	friend class Manager;
};
}
