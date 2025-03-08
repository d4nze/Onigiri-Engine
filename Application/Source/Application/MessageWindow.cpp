#include "MessageWindow.hpp"
#include <Windows.h>

MessageWindow::PressedButton MessageWindow::show(const std::string& title,
												 const std::string& message,
												 Buttons buttons,
												 Icon icon,
												 DefaultButton defaultButton)
{
	std::int32_t result = MessageBoxA(nullptr,
									  message.c_str(),
									  title.c_str(),
									  UINT(buttons) | UINT(icon) | UINT(defaultButton));
	return static_cast<PressedButton>(result);
}
