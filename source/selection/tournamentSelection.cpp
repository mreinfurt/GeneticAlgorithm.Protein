#include "tournamentSelection.h"

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="size">The size.</param>
/// <param name="winrate">The winrate.</param>
TournamentSelection::TournamentSelection(int size, int winrate) : m_TournamentSize(size), m_WinRate(winrate)
{
}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
TournamentSelection::~TournamentSelection(void)
{
}

/// <summary>
/// Selects a number of conformation from the given conformations vector.
/// This is done using basic tournament selection with the tournament size specified in the constructor
/// </summary>
/// <param name="conformations">The conformations.</param>
void TournamentSelection::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;
	for (unsigned int i = 0; i < conformations.size(); ++i)
	{
		// Select conformations
		if (m_TournamentSize <= 2)
		{
			int conformation1 = rand() % conformations.size();
			int conformation2 = rand() % conformations.size();

			int random = rand() % 100;

			// Conformation 1 = best
			if (old[conformation1].getEnergy() > old[conformation2].getEnergy())
			{
				if (random < m_WinRate)
				{
					conformations[i] = old[conformation1];
				}
				else 
				{
					conformations[i] = old[conformation2];
				}
			}
			
			// Conformation 2 = best
			else
			{
				if (random < m_WinRate)
				{
					conformations[i] = old[conformation2];
				}
				else 
				{
					conformations[i] = old[conformation1];
				}
			}
		}
		else
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
}