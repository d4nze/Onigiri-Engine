#pragma once
#include "ProjectCreation.hpp"
#include "ProjectSelection.hpp"
#include "ProjectImporting.hpp"

#include <typeindex>

class GUIState
{
public:
	GUIState(std::type_index typeID);

public:
	template<class TState>
	void setState();
	template<class TState>
	bool is() const;

private:
	void setState(std::type_index typeID);

private:
	std::type_index m_typeID;
};

template void GUIState::setState<ProjectSelection>();
template void GUIState::setState<ProjectCreation>();
template void GUIState::setState<ProjectImporting>();

#include "GUIState.inl"
