#include "LauncherState.hpp"

LauncherState::LauncherState(std::type_index typeID) : m_typeID(typeID) {}

template<class TState>
inline void LauncherState::setState()
{
	m_typeID = typeid(TState);
}

void LauncherState::setState(std::type_index typeID)
{
	m_typeID = typeID;
}
