#pragma once
#include "AssetsBrowser.hpp"
#include "Inspector.hpp"

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

	AssetsBrowser::AssetsBrowser& getAssetsBrowser();
	const AssetsBrowser::AssetsBrowser& getAssetsBrowser() const;

	Inspector& getInspector();
	const Inspector& getInspector() const;

private:
	void showWindow(Window& window);

private:
	AssetsBrowser::AssetsBrowser mAssetsBrowser;
	Inspector mInspector;
};
}
}
