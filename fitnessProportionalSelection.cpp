#include "fitnessProportionalSelection.h"


FitnessProportionalSelection::FitnessProportionalSelection(void)
{
}


FitnessProportionalSelection::~FitnessProportionalSelection(void)
{
}

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
