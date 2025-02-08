#include "ProjectCreationStep.hpp"

ProjectCreationStep::ProjectCreationStep(std::type_index typeID) : m_typeID(typeID) {}

template<class TStep>
inline void ProjectCreationStep::setStep()
{
	m_typeID = typeid(TStep);
}
