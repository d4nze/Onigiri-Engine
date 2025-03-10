#include "Main.hpp"
#include "Application.hpp"

std::int32_t main()
{
	Launcher::Application application;
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
