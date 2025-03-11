#include "Frame.hpp"

template<class TFrame>
inline bool ApplicationCore::Frame::moveToNeighbour()
{
	return moveToNeighbour(typeid(TFrame));
}
