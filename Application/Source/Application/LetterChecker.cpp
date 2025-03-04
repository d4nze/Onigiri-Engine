#include "LetterChecker.hpp"

bool LetterChecker::isNumerical(char letter)
{
    return letter >= '0' && letter <= '9';
}

bool LetterChecker::isLatin(char letter)
{
    return letter >= 'a' && letter <= 'z'
        || letter >= 'A' && letter <= 'Z';
}
