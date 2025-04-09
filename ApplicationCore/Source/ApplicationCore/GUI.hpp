#pragma once

struct ImGuiIO;
struct ImFont;

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

protected:
	ImGuiIO& mImGuiIO;
	ImFont* mMainFont;
};
}
