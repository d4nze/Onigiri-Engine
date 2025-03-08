#include "GUIState.hpp"

GUIState::GUIState(std::type_index typeID) : m_typeID(typeID) {}

template<class TState>
inline void GUIState::setState()
{
	m_typeID = typeid(TState);
}

void GUIState::setState(std::type_index typeID)
{
	m_typeID = typeID;
}
