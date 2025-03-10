#include "Frame.hpp"

template<typename TFrame>
inline bool ApplicationCore::Frame::moveDown()
{
	return moveDown(typeid(TFrame));
}

template<typename TFrame>
inline TFrame* ApplicationCore::Frame::getNeighbour()
{
	return getNeighbour(typeid(TFrame));
}

template<typename TFrame>
inline const TFrame* ApplicationCore::Frame::getNeighbour() const
{
	return getNeighbour(typeid(TFrame));
}

template<typename TFrame>
inline bool ApplicationCore::Frame::addNeighbour(Frame* frame)
{
	return addNeighbour(frame, typeid(TFrame));
}
