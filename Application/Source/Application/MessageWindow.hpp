#pragma once
#include "ApplicationAPI.hpp"
#include <string>

class MessageWindow
{
public:
	enum class Buttons
	{
		AbortRetryIgnore	= 0x00000002L,
		CancelTryContinue	= 0x00000006L,
		Ok					= 0x00000000L,
		OkCancel			= 0x00000001L,
		RetryCancel			= 0x00000005L,
		YesNo				= 0x00000004L,
		YesNoCancel			= 0x00000003L
	};
	enum class Icon
	{
		Exclamation			= 0x00000030L,
		Warning				= 0x00000030L,
		Information			= 0x00000040L,
		Asterisk			= 0x00000040L,
		Question			= 0x00000020L,
		Stop				= 0x00000010L,
		Error				= 0x00000010L,
		Hand				= 0x00000010L
	};
	enum class DefaultButton
	{
		First				= 0x00000000L,
		Second				= 0x00000100L,
		Third				= 0x00000200L,
		Fourth				= 0x00000300L
	};
	enum class PressedButton
	{
		Nothing				= 0,
		Ok					= 1,
		Cancel				= 2,
		Abort				= 3,
		Retry				= 4,
		Ignore				= 5,
		yes					= 6,
		No					= 7,
		TryAgain			= 10,
		Continue			= 11
	};

public:
	static PressedButton show(const std::string& title,
							  const std::string& message,
							  Buttons buttons,
							  Icon icon,
							  DefaultButton defaultButton = DefaultButton::First);
};
