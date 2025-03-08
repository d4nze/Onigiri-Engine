#pragma once

namespace ApplicationCore
{
class LetterChecker
{
public:
	LetterChecker() = delete;

public:
	static bool isNumerical(char letter);
	static bool isLatin(char letter);
};
}
