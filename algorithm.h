#pragma once
#include "element.h"
#include <array>
#include <string>
#include "population.h"
#include <fstream>

class Algorithm {
	public:
		Algorithm(sf::RenderWindow &renderWindow);
		~Algorithm();

		// Draws one specific conformation
		void draw();

		// Runs the algorithm
		void run(bool output);
		
		void update();
		void setUp(int maxGeneration, int populationSize, std::string &chain, float mutationRate, float crossoverRate, Selection *selection);

		float gAvg;
		int gBestEnergy;

		// Returns the energy of the draw conformation
		int getEnergy() { return m_Energy; }
private:		
		// Render
		sf::RenderWindow &m_RenderWindow;
		Conformation *m_DrawConformation;

		Population *m_Population;
		int m_Generation;
		std::ofstream m_Logfile;

		int m_MaxGeneration;
		float m_MutationRate;
		float m_CrossoverRate;
		std::string m_Chain;

		int m_Energy;
};