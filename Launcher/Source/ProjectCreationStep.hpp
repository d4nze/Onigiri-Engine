#pragma once
#include "ProjectNameConfiguration.hpp"
#include "ProjectPathConfiguration.hpp"

#include <typeindex>

class ProjectCreationStep
{
public:
	ProjectCreationStep(std::type_index typeID);

public:
	template<class TStep>
	void setStep();
	template<class TStep>
	bool is() const;

private:
	std::type_index m_typeID;
};

template void ProjectCreationStep::setStep<ProjectNameConfiguration>();
template void ProjectCreationStep::setStep<ProjectPathConfiguration>();

#include "ProjectCreationStep.inl"
