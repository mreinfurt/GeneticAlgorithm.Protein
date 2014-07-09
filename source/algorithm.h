#pragma once
#include "element.h"
#include <array>
#include <string>
#include "population.h"
#include <fstream>

/// <summary>
/// Implements a genetic algorithm
/// </summary>
class Algorithm {
	public:
		// Ctor / Dtor
		Algorithm(sf::RenderWindow &renderWindow);
		~Algorithm();

		// Draws one specific conformation
		void draw();

		// Runs the algorithm without render window
		void run(bool output);
		
		// Runs the algorithm while rendering conformations
		void update();

		// Set up all parameters
		void setUp(int maxGeneration, int populationSize, std::string &chain, float mutationRate, float crossoverRate, Selection *selection, std::string &file = (std::string)"logs/average.txt");

		// Returns the energy of the draw conformation
		int getEnergy() { return m_Energy; }

		// Returns the average fitness of the current generation
		float getAverageFitness() const { return m_AverageFitness; }

		// Returns the best energy value of the current generation
		int getBestEnergy() const { return m_BestEnergy; }

	private:		
		// Render
		sf::RenderWindow &m_RenderWindow;
		Conformation *m_DrawConformation;

		// Population and output
		Population *m_Population;
		int m_Generation;
		std::ofstream m_Logfile;

		// Algorithm parameters
		int m_MaxGeneration;
		float m_MutationRate;
		float m_CrossoverRate;
		std::string m_Chain;

		// Algorithm information
		float m_AverageFitness;
		int m_BestEnergy;
		int m_Energy;
};