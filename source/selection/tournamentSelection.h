#pragma once
#include "../selection.h"

class TournamentSelection : public Selection
{
public:
	TournamentSelection(int size, int winrate);
	virtual ~TournamentSelection(void);

	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
	int m_WinRate;
};

