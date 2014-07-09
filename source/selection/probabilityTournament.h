#pragma once
#include "../selection.h"
class ProbabilityTournament : public Selection
{
public:
	ProbabilityTournament(int size, float winRate);
	virtual ~ProbabilityTournament(void);

	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
	float m_WinRate;
};

