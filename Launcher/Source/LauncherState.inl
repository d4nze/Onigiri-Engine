#include "LauncherState.hpp"

template<class TState>
inline bool LauncherState::is() const
{
	return m_typeID == typeid(TState);
}