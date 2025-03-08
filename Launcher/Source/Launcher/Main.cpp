#include "Main.hpp"
#include "Application.hpp"

#include <shobjidl.h>

std::int32_t main()
{
	Application application;
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
