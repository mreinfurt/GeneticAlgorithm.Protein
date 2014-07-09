#include "fitnessProportionalSelection.h"


/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
FitnessProportionalSelection::FitnessProportionalSelection(void)
{
}


/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
FitnessProportionalSelection::~FitnessProportionalSelection(void)
{
}

/// <summary>
/// Selects a number of conformation from the given conformations vector.
/// This is a fitness proportional selection, so that conformations with a higher energy value also have a higher chance of getting selected.
/// </summary>
/// <param name="conformations">The conformations.</param>
void FitnessProportionalSelection::select(std::vector<Conformation> &conformations)
{
	std::vector<Conformation> old = conformations;

	int cumulativeEnergy = 0;
	for (unsigned int i = 0;i < conformations.size(); ++i)
	{
		cumulativeEnergy += conformations[i].getEnergy();
	}

	for (unsigned int i = 0;i < conformations.size(); ++i)
	{
		int random = rand() % (int) cumulativeEnergy;
		int sumFitness = 0;

		for (unsigned int j = 0; j < conformations.size(); ++j)
		{
			sumFitness += old.at(j).getEnergy();
			if(sumFitness > random)
			{
				conformations[i] = old[j];
				break;
			}
		}
	}
}
