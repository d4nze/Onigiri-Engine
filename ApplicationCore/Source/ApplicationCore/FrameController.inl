#include "FrameController.hpp"

template<class TFrame>
inline bool ApplicationCore::FrameController::setCurrentFrame()
{
	return setCurrentFrame(typeid(TFrame));
}

template<class TFrame>
inline bool ApplicationCore::FrameController::isCurrentFrame() const
{
	return isCurrentFrame(typeid(TFrame));
}

template<class TFrame>
inline TFrame* ApplicationCore::FrameController::addFrame(Frame* frame)
{
	if (dynamic_cast<TFrame*>(frame) == nullptr)
	{
		delete frame;
		return nullptr;
	}
	return reinterpret_cast<TFrame*>(addFrame(frame, typeid(TFrame)));
}

template<class TFrame>
inline bool ApplicationCore::FrameController::hasFrame() const
{
	return hasFrame(typeid(TFrame));
}

template<class TFrame>
inline TFrame* ApplicationCore::FrameController::getFrame()
{
	return getFrame(typeid(TFrame));
}

template<class TFrame>
inline const TFrame* ApplicationCore::FrameController::getFrame() const
{
	return getFrame(typeid(TFrame));
}
