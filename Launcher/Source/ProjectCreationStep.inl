#include "ProjectCreationStep.hpp"

template<class TStep>
inline bool ProjectCreationStep::is() const
{
	return m_typeID == typeid(TStep);
}
