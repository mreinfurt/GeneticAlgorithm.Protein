#include "probabilityTournament.h"

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="size">The size.</param>
/// <param name="winRate">The win rate.</param>
ProbabilityTournament::ProbabilityTournament(int size, float winRate) : m_TournamentSize(size), m_WinRate(winRate)
{

}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
/// <returns></returns>
ProbabilityTournament::~ProbabilityTournament(void)
{

}

/// <summary>
/// Compares two conformations and returns true if the energy of the first conformation is the lower one.
/// </summary>
/// <param name="i">The i.</param>
/// <param name="j">The j.</param>
/// <returns></returns>
bool compare2Conformations(Conformation *i, Conformation *j) 
{ 
	int energy1 = i->getEnergy();
	int energy2 = j->getEnergy();

	return energy1 < energy2; 
}

/// <summary>
/// Selects a number of conformation from the given conformations vector.
/// </summary>
/// <param name="conformations">The conformations.</param>
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
			float realRandom = random / 100.0f;
			
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