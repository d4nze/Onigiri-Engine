#include "Frame.hpp"

template<class TFrame>
inline bool ApplicationCore::Frame::moveToNeighbour()
{
	return moveToNeighbour(typeid(TFrame));
}

template<class TFrame>
inline bool ApplicationCore::Frame::addNeighbour()
{
	return addNeighbour(typeid(TFrame));
}

template<class TFrame>
inline bool ApplicationCore::Frame::hasNeighbour() const
{
	return hasNeighbour(typeid(TFrame));
}

template<class TFrame>
inline TFrame* ApplicationCore::Frame::getNeighbour()
{
	return reinterpret_cast<TFrame*>(getNeighbour(typeid(TFrame)));
}

template<class TFrame>
inline const TFrame* ApplicationCore::Frame::getNeighbour() const
{
	return reinterpret_cast<TFrame*>(getNeighbour(typeid(TFrame)));
}
