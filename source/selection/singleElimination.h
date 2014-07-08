#pragma once
#include "../selection.h"
class SingleElimination : public Selection
{
public:
	SingleElimination(int size, int winRate);
	virtual ~SingleElimination(void);

	virtual void select(std::vector<Conformation> &conformations);

private:
	int m_TournamentSize;
	float m_WinRate;
};

