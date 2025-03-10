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
	virtual ~Frame();

public:
	template<typename TFrame>
	bool moveDown();
	bool moveUp();

	FrameController& getController();
	const FrameController& getController() const;

	template<typename TFrame>
	TFrame* getParent();
	template<typename TFrame>
	const TFrame* getParent() const;

	template<typename TFrame>
	TFrame* getNeighbour();
	template<typename TFrame>
	const TFrame* getNeighbour() const;

protected:
	virtual void show() {};

	template<typename TFrame>
	bool setParent(Frame* frame);
	template<typename TFrame>
	bool addNeighbour(Frame* frame);

private:
	bool moveDown(std::type_index frameIDType);
	Frame* getParent(std::type_index frameIDType) const;
	Frame* getNeighbour(std::type_index frameIDType);
	const Frame* getNeighbour(std::type_index frameIDType) const;
	bool setParent(Frame* frame, std::type_index frameIDType);
	bool addNeighbour(Frame* frame, std::type_index frameIDType);

private:
	FrameController& m_controller;
	std::pair<Frame*, std::type_index> m_parent;
	std::map<std::type_index, Frame*> m_neighbours;

	friend FrameController;
};
}

#include "Frame.inl"
