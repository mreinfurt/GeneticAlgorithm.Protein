#include "probabilityTournament.h"
#include <math.h>

ProbabilityTournament::ProbabilityTournament(int size, int winRate) : m_TournamentSize(size), m_WinRate(winRate)
{

}

ProbabilityTournament::~ProbabilityTournament(void)
{

}

void ProbabilityTournament::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;
	for (int i = 0; i < conformations.size(); ++i)
	{
		std::vector<Conformation*> sorted(m_TournamentSize);

		for (int k = 0; k < m_TournamentSize - 1; ++k)
		{
			int random = rand() % conformations.size();

			// Sort random into vector
			sorted[k] = &old[random];
		}

		std::sort(sorted.begin(), sorted.end());

		// Choose winner
		bool selected = false;
		int counter = 0;
		while (!selected)
		{			
			int random = rand() % 100;
			int winRate = m_WinRate * pow((1 - m_WinRate), counter);

			if (random < winRate)
			{
				selected = true;
				conformations[i] = *sorted[conformations.size() - counter];
			}

			counter++;
		}
	}
}