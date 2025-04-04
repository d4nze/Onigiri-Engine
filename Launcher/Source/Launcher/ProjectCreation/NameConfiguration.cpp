#include "NameConfiguration.hpp"
#include "PathConfiguration.hpp"
#include "ApplicationCore/LetterChecker.hpp"

#include <imgui.h>

Launcher::ProjectCreation::NameConfiguration::NameConfiguration(ApplicationCore::FrameController& createController)
    : ApplicationCore::Frame(createController)
    , mBufferSize(255)
    , mName(mBufferSize, '\0')
    , mErrorType(ErrorType::NoError)
	, mPreviousErrorType(mErrorType)
	, mErrorText("")
{
	updateErrorType();
}

void Launcher::ProjectCreation::NameConfiguration::reset()
{
    mName = std::string(mBufferSize, '\0');
	mErrorType = ErrorType::NoError;
	mPreviousErrorType = mErrorType;
}

void Launcher::ProjectCreation::NameConfiguration::updateErrorType()
{
	if (mErrorType != ErrorType::NoError)
	{
		mPreviousErrorType = mErrorType;
	}
	mErrorType = ErrorType::NoError;
	const char fisrtLetter = mName[0];
	if (fisrtLetter == '\0')
	{
		mErrorType = ErrorType::Empty;
		return;
	}
	if (fisrtLetter == ' ')
	{
		mErrorType = ErrorType::Space;
		return;
	}
	if (fisrtLetter != '_' && !ApplicationCore::LetterChecker::isLatin(fisrtLetter))
	{
		if (!ApplicationCore::LetterChecker::isNumerical(fisrtLetter))
		{
			mErrorType = ErrorType::UnsupportedCharacter;
			return;
		}
		mErrorType = ErrorType::FirstLetter;
		return;
	}
	for (std::int32_t i = 0; i < mBufferSize; i++)
	{
		const char letter = mName[i];
		if (letter == '\0')
		{
			return;
		}
		if (letter == ' ')
		{
			mErrorType = ErrorType::Space;
			return;
		}
		if (letter != '_' &&
			!ApplicationCore::LetterChecker::isLatin(letter) &&
			!ApplicationCore::LetterChecker::isNumerical(letter))
		{
			mErrorType = ErrorType::UnsupportedCharacter;
			return;
		}
	}
}

bool Launcher::ProjectCreation::NameConfiguration::hasError()
{
	return mErrorType != ErrorType::NoError;
}

bool Launcher::ProjectCreation::NameConfiguration::moveNext()
{
	return moveToNeighbour<PathConfiguration>();
}

std::string Launcher::ProjectCreation::NameConfiguration::getName() const
{
    return mName.c_str();
}

Launcher::ProjectCreation::NameConfiguration::ErrorType Launcher::ProjectCreation::NameConfiguration::getError() const
{
    return mErrorType;
}

void Launcher::ProjectCreation::NameConfiguration::show()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", mName.data(), mBufferSize))
	{
		updateErrorType();
		if (PathConfiguration* pathConfiguration = getNeighbour<PathConfiguration>())
		{
			pathConfiguration->updateErrorType();
		}
	}
	if (mErrorType != ErrorType::NoError)
	{
		if (mErrorType != mPreviousErrorType)
		{
			mPreviousErrorType = mErrorType;
			updateErrorText();
		}
		showError();
	}
}

void Launcher::ProjectCreation::NameConfiguration::showError()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
	ImGui::Text(mErrorText.c_str());
	ImGui::PopStyleColor();
}

void Launcher::ProjectCreation::NameConfiguration::updateErrorText()
{
	switch (mErrorType)
	{
	case ErrorType::Empty:
		mErrorText = "Name is not writen";
		break;
	case ErrorType::FirstLetter:
		mErrorText = "Name must start with latin symbol or '_'";
		break;
	case ErrorType::Space:
		mErrorText = "Name cannot have spaces";
		break;
	case ErrorType::UnsupportedCharacter:
		mErrorText = "Name must consist only of lating symbols, numbers and '_'";
		break;
	}
}
