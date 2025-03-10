#include "Frame.hpp"

template<typename TFrame>
inline bool ApplicationCore::Frame::moveDown()
{
	return moveDown(typeid(TFrame));
}

template<typename TFrame>
inline TFrame* ApplicationCore::Frame::getParent()
{
	return getParent(typeid(TFrame));
}

template<typename TFrame>
inline const TFrame* ApplicationCore::Frame::getParent() const
{
	return getParent(typeid(TFrame));
}

template<typename TFrame>
inline TFrame* ApplicationCore::Frame::getChild()
{
	return getChild(typeid(TFrame));
}

template<typename TFrame>
inline const TFrame* ApplicationCore::Frame::getChild() const
{
	return getChild(typeid(TFrame));
}

template<typename TFrame>
inline bool ApplicationCore::Frame::setParent(Frame* frame)
{
	return setParent(frame, typeid(TFrame));
}

template<typename TFrame>
inline bool ApplicationCore::Frame::addChildren(Frame* frame)
{
	return addChildren(frame, typeid(TFrame));
}
