#include "Main.hpp"
#include "LauncherApplication.hpp"

#include <shobjidl.h>

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
