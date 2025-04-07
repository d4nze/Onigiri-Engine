#pragma once
#include "Inspectable.hpp"
#include "Window.hpp"

namespace ProjectEditor::Window
{
class Inspector : public Window
{
public:
	Inspector(GUI& gui, bool open = false);

public:
	void show() override;

	void setInspectable(Inspectable* inspectable);
	Inspectable* getInspectable();
	const Inspectable* getInspectable() const;

private:
	Inspectable* mInspectable;
};
}
