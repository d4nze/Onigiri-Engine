#include "Frame.hpp"
#include "FrameController.hpp"

ApplicationCore::Frame::Frame(FrameController& controller) : mController(controller)
{}

ApplicationCore::FrameController& ApplicationCore::Frame::getController()
{
	return mController;
}

const ApplicationCore::FrameController& ApplicationCore::Frame::getController() const
{
	return mController;
}

bool ApplicationCore::Frame::moveToNeighbour(std::type_index neighbourTypeID)
{
	if (hasNeighbour(neighbourTypeID))
	{
		mController.mCurrentFrame = mController.mFrames.at(neighbourTypeID);
		return true;
	}
	return false;
}

bool ApplicationCore::Frame::addNeighbour(std::type_index neighbourTypeID)
{
	if (hasNeighbour(neighbourTypeID))
	{
		return false;
	}
	mController.mConnections.insert({ *mController.mTypeIDs.at(const_cast<Frame*>(this)), neighbourTypeID });
	return true;
}

bool ApplicationCore::Frame::hasNeighbour(std::type_index neighbourTypeID) const
{
	std::type_index myTypeID = *mController.mTypeIDs.at(const_cast<Frame*>(this));
	return mController.mConnections.find({ myTypeID, neighbourTypeID }) != mController.mConnections.end();
}

ApplicationCore::Frame* ApplicationCore::Frame::getNeighbour(std::type_index neighbourTypeID) const
{
	if (hasNeighbour(neighbourTypeID))
	{
		return mController.mFrames.at(neighbourTypeID);
	}
	return nullptr;
}
