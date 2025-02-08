#include "Main.hpp"
#include "LauncherApplication.hpp"

std::int32_t main()
{
	LauncherApplication application;
	try
	{
		application.run();
	}
	catch (std::exception exception)
	{
		return 1;
	}
	return 0;
}
