#include "probabilityTournament.h"

ProbabilityTournament::ProbabilityTournament(int size, int winRate) : m_TournamentSize(size), m_WinRate(winRate)
{

}

ProbabilityTournament::~ProbabilityTournament(void)
{

}

bool compare2Conformations(Conformation *i, Conformation *j) 
{ 
	int energy1 = i->getEnergy();
	int energy2 = j->getEnergy();

	return energy1 < energy2; 
}

void ProbabilityTournament::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;
	for (unsigned int i = 0; i < conformations.size(); ++i)
	{
		std::vector<Conformation*> sorted(m_TournamentSize);

		for (int k = 0; k < m_TournamentSize; ++k)
		{
			int random = rand() % conformations.size();

			// Sort random into vector
			sorted[k] = &old[random];
		}

		std::sort(sorted.begin(), sorted.end(), compare2Conformations);

		// Choose winner
		bool selected = false;
		int counter = 0;
		while (!selected)
		{			
			int random = rand() % 10000;
			float winRate = m_WinRate * pow((1 - m_WinRate), counter);
			float realRandom = random / 100;
			
			if (realRandom < winRate)
			{
				selected = true;
				conformations[i] = *sorted[m_TournamentSize - counter - 1];
			}

			if (counter >= m_TournamentSize - 1)
			{				
				conformations[i] = *sorted[0];
				selected = true;
			}

			counter++;
		}
	}
}