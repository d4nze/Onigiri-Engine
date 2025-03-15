#pragma once
#include "Frame.hpp"

#include <map>
#include <optional>
#include <set>
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
	Frame* getCurrentFrame();
	const Frame* getCurrentFrame() const;

	Application& getApplication();
	const Application& getApplication() const;

	template<class TFrame>
	TFrame* addFrame(Frame* frame);
	template<class TFrame>
	bool hasFrame() const;
	template<class TFrame>
	TFrame* getFrame();
	template<class TFrame>
	const TFrame* getFrame() const;

private:
	bool setCurrentFrame(std::type_index frameTypeID);
	bool isCurrentFrame(std::type_index frameTypeID) const;

	Frame* addFrame(Frame* frame, std::type_index frameTypeID);
	bool hasFrame(std::type_index frameTypeID) const;
	Frame* getFrame(std::type_index frameTypeID) const;

private:
	Application& m_application;
	Frame* m_currentFrame;
	std::map<std::type_index, Frame*> m_frames;
	std::map<Frame*, std::optional<std::type_index>> m_typeIDs;
	std::set<std::pair<std::type_index, std::type_index>> m_connections;

	friend Frame;
};
}

#include "FrameController.inl"
