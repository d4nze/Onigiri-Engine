#pragma once
#include "Frame.hpp"

#include <map>
#include <vector>

namespace ApplicationCore
{
class APPLICATION_CORE_API Application;

class FrameController
{
public:
	FrameController(Application& application);
	~FrameController();

public:
	void show();

	template<class TFrame>
	bool setCurrentFrame();
	template<class TFrame>
	bool isCurrentFrame() const;

	Application& getApplication();
	const Application& getApplication() const;

	template<class TFrame>
	TFrame* addFrame(Frame* frame);
	template<class TFrame>
	TFrame* getFrame();
	template<class TFrame>
	const TFrame* getFrame() const;

	template<class TFrame>
	bool addNeighbour(Frame* frame);
	template<class TFrame>
	bool hasNeighbour(Frame* frame) const;
	template<class TFrame>
	TFrame* getNeighbour(Frame* frame);
	template<class TFrame>
	const TFrame* getNeighbour(Frame* frame) const;

private:
	bool setCurrentFrame(std::type_index frameTypeID);
	bool isCurrentFrame(std::type_index frameTypeID) const;

	Frame* addFrame(Frame* frame, std::type_index frameTypeID);
	Frame* getFrame(std::type_index frameTypeID) const;

	bool addNeighbour(Frame* frame, std::type_index neighbourTypeID);
	bool hasNeighbour(Frame* frame, std::type_index neighbourTypeID) const;
	Frame* getNeighbour(Frame* frame, std::type_index neighbourTypeID) const;

private:
	Application& m_application;
	Frame* m_currentFrame;
	std::map<std::type_index, Frame*> m_frames;

	friend Frame;
};
}

#include "FrameController.inl"
