#include "Main.hpp"
#include "MainApplication.hpp"

#ifdef DEBUG
#include <iostream>
#define SHOW_ERROR(message) std::cout << message << "\n";
#else
#defube SHOW_ERROR(message)
#endif

std::int32_t main()
{
	MainApplication application;
	try
	{
		application.run();
	}
	catch (std::exception exception)
	{
		SHOW_ERROR(exception.what());
	}
	return 0;
}
