#pragma once
#include "../selection.h"

class TournamentSelection : public Selection
{
public:
	TournamentSelection(int size, float winrate);
	virtual ~TournamentSelection(void);

	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
	float m_WinRate;
};

