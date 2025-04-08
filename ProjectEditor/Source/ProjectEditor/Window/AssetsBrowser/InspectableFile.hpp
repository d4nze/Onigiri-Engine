#pragma once
#include "../Inspectable.hpp"
#include "File.hpp"

namespace ProjectEditor::Window::AssetsBrowser
{
class InspectableFile : public Inspectable, public File
{
public:
	InspectableFile();

public:
	void update();
	void inspect() override;

private:
	std::optional<std::string> mErrorText;
	std::string mName;
	std::string mExtension;
	float mSize;
};
}
