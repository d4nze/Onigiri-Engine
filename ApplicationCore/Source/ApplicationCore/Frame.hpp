#pragma once
#include "ApplicationAPI.hpp"

#include <typeindex>
#include <set>

namespace ApplicationCore
{
class FrameController;

class Frame
{
public:
	Frame(FrameController& controller);
	virtual ~Frame() = default;

public:
	template<class TFrame>
	bool moveToNeighbour();

	FrameController& getController();
	const FrameController& getController() const;

protected:
	virtual void show() = 0;

private:
	bool moveToNeighbour(std::type_index neighbourTypeID);

private:
	FrameController& m_controller;
	std::set<std::type_index> m_neighbours;

	friend FrameController;
};
}

#include "Frame.inl"
