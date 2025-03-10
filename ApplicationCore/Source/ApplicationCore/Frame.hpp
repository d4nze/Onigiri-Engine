#pragma once
#include "ApplicationAPI.hpp"

#include <map>
#include <typeindex>

namespace ApplicationCore
{
class APPLICATION_CORE_API FrameController;

class APPLICATION_CORE_API Frame
{
public:
	Frame(FrameController& controller);
	virtual ~Frame();

public:
	template<typename TFrame>
	bool moveDown();
	bool moveUp();

	template<typename TFrame>
	TFrame* getParent();
	template<typename TFrame>
	const TFrame* getParent() const;

	template<typename TFrame>
	TFrame* getChild();
	template<typename TFrame>
	const TFrame* getChild() const;

protected:
	virtual void show() = 0;

	template<typename TFrame>
	bool setParent(Frame* frame);
	template<typename TFrame>
	bool addChildren(Frame* frame);

private:
	bool moveDown(std::type_index frameIDType);
	Frame* getParent(std::type_index frameIDType) const;
	Frame* getChild(std::type_index frameIDType);
	const Frame* getChild(std::type_index frameIDType) const;
	bool setParent(Frame* frame, std::type_index frameIDType);
	bool addChildren(Frame* frame, std::type_index frameIDType);

private:
	FrameController& m_controller;
	std::pair<Frame*, std::type_index> m_parent;
	std::map<std::type_index, Frame*> m_children;

	friend FrameController;
};
}

#include "Frame.inl"
