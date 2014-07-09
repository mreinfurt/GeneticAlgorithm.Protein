#pragma once
#include "element.h"
#include "conformation.h"
#include "selection.h"

/// <summary>
/// Represents one generation of the genetic algorithm. A population contains a certain number of conformations.
/// It also has operations which can be executed on the population's inhabitants (conformations).
/// </summary>
class Population
{
public:
	// Creates population and initializes elements vector
	Population(std::string &chain, int populationSize, float mutationRate, float crossoverRate, Selection *selection);
	~Population();

	// Restructures the population and selects 'n' new conformations
	void selection();

	// Selects 'n' random conformations and calls mutate()
	void mutation();

	// Selects 'n' random conformations and calls crossover(conformation)
	void crossover();

	// Calculates all energy values and returns the average fitness
	float evaluation();

	// Creates the initial population
	void createInitialPopulation();

	// Returns the list of conformations
	std::vector<Conformation>& Conformations() { return m_Conformations; }

	// Returns best energy value of this population
	int getBestEnergy() const { return m_BestEnergy; }
	const Conformation& getBestConformation();

private:
	// Elements without a direction
	std::vector<Element> m_Elements;

	// List of conformations
	std::vector<Conformation> m_Conformations;

	// Strategies
	Selection *m_Selection;

	// The original protein chain
	std::string m_Chain;
	float m_CumulativeEnergy;
	int m_BestEnergy;
	int m_PopulationSize;
	float m_MutationRate;
	float m_CrossoverRate;
	float m_CrossoverCount;
	int m_SumFitness;

	Conformation *m_BestConformation;
};