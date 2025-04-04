#include "PathConfiguration.hpp"
#include "NameConfiguration.hpp"
#include "Finalization.hpp"
#include "ApplicationCore/BrowseWindow.hpp"

#include <filesystem>
#include <imgui.h>

Launcher::ProjectCreation::PathConfiguration::PathConfiguration(ApplicationCore::FrameController& createController)
    : ApplicationCore::Frame(createController)
    , mBufferSize(1024)
    , mPath(mBufferSize, '\0')
    , mErrorType(ErrorType::NoError)
    , mPreviousErrorType(mErrorType)
    , mErrorText("")
{}

void Launcher::ProjectCreation::PathConfiguration::reset()
{
    mPath = std::string(mBufferSize, '\0');
    mErrorType = ErrorType::NoError;
    mPreviousErrorType = mErrorType;
}

void Launcher::ProjectCreation::PathConfiguration::updateErrorType()
{
	mErrorType = ErrorType::NoError;
	std::filesystem::path systemPath = mPath;
	if (mPath[0] == '\0')
	{
		mErrorType = ErrorType::Empty;
	}
	else if (systemPath.is_relative())
	{
		mErrorType = ErrorType::RelativePath;
	}
	else if (!std::filesystem::exists(systemPath) && !std::filesystem::is_directory(systemPath))
	{
		mErrorType = ErrorType::InvalidPath;
	}
	else if (NameConfiguration* nameConfiguration = getNeighbour<NameConfiguration>())
	{
		std::string resultPath(mPath.c_str());
		resultPath += "\\";
		resultPath += nameConfiguration->getName();
		if (std::filesystem::exists(resultPath))
		{
			mErrorType = ErrorType::ProjectExists;
		}
	}
}

bool Launcher::ProjectCreation::PathConfiguration::hasError()
{
    return mErrorType != ErrorType::NoError;
}

bool Launcher::ProjectCreation::PathConfiguration::moveBack()
{
    return moveToNeighbour<NameConfiguration>();
}

bool Launcher::ProjectCreation::PathConfiguration::moveNext()
{
	return moveToNeighbour<Finalization>();
}

std::string Launcher::ProjectCreation::PathConfiguration::getPath() const
{
    return mPath.c_str();
}

Launcher::ProjectCreation::PathConfiguration::ErrorType Launcher::ProjectCreation::PathConfiguration::getError() const
{
    return mErrorType;
}

void Launcher::ProjectCreation::PathConfiguration::show()
{
	ImGui::TextUnformatted("Enter project's name");
	if (ImGui::InputText("##Project Name Input", mPath.data(), mBufferSize))
	{
		updateErrorType();
	}
	ImGui::SameLine();
	if (ImGui::Button("Browse", ImVec2(80, 0)))
	{
		std::filesystem::path path = ApplicationCore::BrowseWindow::selectFolder();
		if (!path.empty())
		{
			std::string sPath = path.string();
			mPath = sPath;
			mPath.resize(mBufferSize);
			updateErrorType();
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

void Launcher::ProjectCreation::PathConfiguration::showError()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
	ImGui::Text(mErrorText.c_str());
	ImGui::PopStyleColor();
}

void Launcher::ProjectCreation::PathConfiguration::updateErrorText()
{
	switch (mErrorType)
	{
	case ErrorType::Empty:
		mErrorText = "Please select project folder";
		break;
	case ErrorType::RelativePath:
		mErrorText = "Path must be absolute";
		break;
	case ErrorType::ProjectExists:
		mErrorText = "There is an already existing project with this name";
		break;
	case ErrorType::InvalidPath:
		mErrorText = "Invalid path";
		break;
	}
}
