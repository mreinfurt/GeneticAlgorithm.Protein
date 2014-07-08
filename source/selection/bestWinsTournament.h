#pragma once
#include "../selection.h"

// This selection works like a tournament selection, but the best of the selected conformations always wins
class BestWinsTournament : public Selection
{
public:
	BestWinsTournament(int size);
	virtual ~BestWinsTournament(void);
	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
};

