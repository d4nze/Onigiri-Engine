#pragma once
#include "ApplicationCore/Frame.hpp"
#include "IStep.hpp"

#include <string>

namespace Launcher
{
namespace ProjectCreation
{
class PathConfiguration : public ApplicationCore::Frame, public IStep
{
public:
	PathConfiguration(ApplicationCore::FrameController& createController);

public:
	enum class ErrorType
	{
		NoError,
		Empty,
		RelativePath,
		ProjectExists,
		InvalidPath
	};

public:
	void reset();
	void updateErrorType();

	bool hasError() override;
	bool moveBack() override;
	bool moveNext() override;

	std::string getPath() const;
	ErrorType getError() const;

protected:
	void show();

private:
	void showError();
	void updateErrorText();

private:
	const std::int32_t m_bufferSize;
	std::string m_path;
	ErrorType m_errorType;
	ErrorType m_previousErrorType;
	std::string m_errorText;
};
}
}
