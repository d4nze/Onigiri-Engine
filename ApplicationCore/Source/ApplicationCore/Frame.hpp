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
	template<class TFrame>
	bool addNeighbour();
	template<class TFrame>
	bool hasNeighbour() const;
	template<class TFrame>
	TFrame* getNeighbour();
	template<class TFrame>
	const TFrame* getNeighbour() const;

	FrameController& getController();
	const FrameController& getController() const;

protected:
	virtual void show() = 0;

private:
	bool moveToNeighbour(std::type_index neighbourTypeID);
	bool addNeighbour(std::type_index neighbourTypeID);
	bool hasNeighbour(std::type_index neighbourTypeID) const;
	Frame* getNeighbour(std::type_index neighbourTypeID) const;

private:
	FrameController& m_controller;

	friend FrameController;
};
}

#include "Frame.inl"
