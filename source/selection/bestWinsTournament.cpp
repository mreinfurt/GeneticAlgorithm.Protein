#include "bestWinsTournament.h"


/// <summary>
/// Bests the wins tournament.
/// </summary>
/// <param name="size">The size.</param>
/// <returns></returns>
BestWinsTournament::BestWinsTournament(int size) : m_TournamentSize(size)
{
}


/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
BestWinsTournament::~BestWinsTournament(void)
{
}

/// <summary>
/// Selects a number of conformation from the given conformations vector.
/// This randomly selects a number of attendees, the best attendee always wins.
/// </summary>
/// <param name="conformations">The conformations.</param>
void BestWinsTournament::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;
	for (unsigned int i = 0; i < conformations.size(); ++i)
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