#include "GUIState.hpp"

template<class TState>
inline bool GUIState::is() const
{
	return m_typeID == typeid(TState);
}