#pragma once
#include "ProjectCreation.hpp"
#include "ProjectSelection.hpp"
#include "ProjectImporting.hpp"

#include <typeindex>

class LauncherState
{
public:
	LauncherState(std::type_index typeID);

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

template void LauncherState::setState<ProjectSelection>();
template void LauncherState::setState<ProjectCreation>();
template void LauncherState::setState<ProjectImporting>();

#include "LauncherState.inl"
