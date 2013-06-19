#pragma once
#include "selection.h"
class FitnessProportionalSelection :
	public Selection
{
public:
	FitnessProportionalSelection(void);
	virtual ~FitnessProportionalSelection(void);

	virtual void select(std::vector<Conformation> &conformations);
};

