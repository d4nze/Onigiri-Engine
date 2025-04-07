#pragma once
#include "AssetsBrowser.hpp"

namespace ProjectEditor
{
namespace Window
{
class WindowHolder
{
public:
	WindowHolder(GUI& gui);

public:
	void show();

	AssetsBrowser& getAssetsBrowser();
	const AssetsBrowser& getAssetsBrowser() const;

private:
	void showWindow(Window& window);

private:
	AssetsBrowser mAssetsBrowser;
};
}
}
