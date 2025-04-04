#include "FrameController.hpp"

#include <algorithm>
#include <vector>

ApplicationCore::FrameController::FrameController(Application& application)
	: mApplication(application)
	, mCurrentFrame(nullptr)
{}

ApplicationCore::FrameController::~FrameController()
{
	for (std::pair<std::type_index, Frame*> frameHolder : mFrames)
	{
		delete frameHolder.second;
	}
}

void ApplicationCore::FrameController::show()
{
	if (mCurrentFrame != nullptr)
	{
		mCurrentFrame->show();
	}
}

ApplicationCore::Frame* ApplicationCore::FrameController::getCurrentFrame()
{
	return mCurrentFrame;
}

const ApplicationCore::Frame* ApplicationCore::FrameController::getCurrentFrame() const
{
	return mCurrentFrame;
}

ApplicationCore::Application& ApplicationCore::FrameController::getApplication()
{
	return mApplication;
}

const ApplicationCore::Application& ApplicationCore::FrameController::getApplication() const
{
	return mApplication;
}

bool ApplicationCore::FrameController::setCurrentFrame(std::type_index frameTypeID)
{
	if (hasFrame(frameTypeID))
	{
		mCurrentFrame = mFrames.at(frameTypeID);
		return true;
	}
	return false;
}

bool ApplicationCore::FrameController::isCurrentFrame(std::type_index frameTypeID) const
{
	std::map<std::type_index, Frame*>::const_iterator it = mFrames.find(frameTypeID);
	if (it == mFrames.end())
	{
		return false;
	}
	return it->second == mCurrentFrame;
}

ApplicationCore::Frame* ApplicationCore::FrameController::addFrame(Frame* frame, std::type_index frameTypeID)
{
	if (hasFrame(frameTypeID))
	{
		delete frame;
		return nullptr;
	}
	mFrames[frameTypeID] = frame;
	mTypeIDs[frame] = frameTypeID;
	return frame;
}

bool ApplicationCore::FrameController::hasFrame(std::type_index frameTypeID) const
{
	return mFrames.find(frameTypeID) != mFrames.end();
}

ApplicationCore::Frame* ApplicationCore::FrameController::getFrame(std::type_index frameTypeID) const
{
	if (hasFrame(frameTypeID))
	{
		return mFrames.at(frameTypeID);
	}
	return nullptr;
}
