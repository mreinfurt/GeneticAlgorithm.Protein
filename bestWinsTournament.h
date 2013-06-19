#pragma once
#include "selection.h"
class BestWinsTournament : public Selection
{
public:
	BestWinsTournament(int size);
	virtual ~BestWinsTournament(void);
	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
};

