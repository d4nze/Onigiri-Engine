#pragma once
#include "../Inspectable.hpp"
#include "File.hpp"

namespace ApplicationCore::Font
{
class Manager;
}

namespace ProjectEditor::Window::AssetsBrowser
{
class InspectableFile : public Inspectable, public File
{
public:
	InspectableFile(ApplicationCore::Font::Manager& fontManager);

public:
	void update();
	void inspect() override;

private:
	ApplicationCore::Font::Manager& mFontManager;
	std::optional<std::string> mErrorText;
	std::string mName;
	std::string mExtension;
	float mSize;
};
}
