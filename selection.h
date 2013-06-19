#pragma once

#include <vector>
#include "conformation.h"

class Selection
{
public:
	Selection(void);
	virtual ~Selection(void);	
	virtual void select(std::vector<Conformation> &conformations) = 0;
};
