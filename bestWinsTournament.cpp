#include "bestWinsTournament.h"


BestWinsTournament::BestWinsTournament(int size) : m_TournamentSize(size)
{
}


BestWinsTournament::~BestWinsTournament(void)
{
}

void BestWinsTournament::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;
	for (int i = 0; i < conformations.size(); ++i)
	{
		Conformation &bestConformation = conformations[rand() % conformations.size()];
		for (int k = 0; k < m_TournamentSize - 1; ++k)
		{
			int random = rand() % conformations.size();
			if (old[random].getEnergy() > bestConformation.getEnergy())
			{
				bestConformation = old[random];
			}
			
			conformations[i] = bestConformation;
		}
	}
}