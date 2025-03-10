#pragma once
#include "ApplicationAPI.hpp"

#include <map>
#include <typeindex>

namespace ApplicationCore
{
class APPLICATION_CORE_API FrameController;

class Frame
{
public:
	Frame(FrameController& controller);
	virtual ~Frame() = default;

public:
	template<typename TFrame>
	bool moveDown();

	FrameController& getController();
	const FrameController& getController() const;

	template<typename TFrame>
	TFrame* getNeighbour();
	template<typename TFrame>
	const TFrame* getNeighbour() const;

protected:
	virtual void show() {};

	template<typename TFrame>
	bool addNeighbour(Frame* frame);

private:
	bool moveDown(std::type_index frameIDType);
	Frame* getNeighbour(std::type_index frameIDType);
	const Frame* getNeighbour(std::type_index frameIDType) const;
	bool addNeighbour(Frame* frame, std::type_index frameIDType);

private:
	FrameController& m_controller;
	std::map<std::type_index, Frame*> m_neighbours;

	friend FrameController;
};
}

#include "Frame.inl"
