#pragma once

#include <vector>
#include "conformation.h"

/// <summary>
/// Interface for different selection strategies
/// </summary>
class Selection
{
public:
	Selection(void) {};
	virtual ~Selection(void) {};	

	// Selects a new population and alters the reference
	virtual void select(std::vector<Conformation> &conformations) = 0;
};
