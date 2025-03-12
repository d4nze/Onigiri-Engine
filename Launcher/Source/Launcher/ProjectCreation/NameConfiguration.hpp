#pragma once
#include "ApplicationCore/Frame.hpp"
#include "IStep.hpp"

#include <string>

namespace Launcher
{
namespace ProjectCreation
{
class NameConfiguration : public ApplicationCore::Frame, public IStep
{
public:
	NameConfiguration(ApplicationCore::FrameController& createController);

public:
	enum class ErrorType
	{
		NoError,
		Empty,
		FirstLetter,
		Space,
		UnsupportedCharacter
	};

public:
	void reset();
	void updateErrorType();

	bool hasError() override;

	const std::string& getName() const;
	ErrorType getError() const;

protected:
	void show();

private:
	void showError();
	void updateErrorText();

private:
	const std::int32_t m_bufferSize;
	std::string m_name;
	ErrorType m_errorType;
	ErrorType m_previousErrorType;
	std::string m_errorText;
};
}
}
