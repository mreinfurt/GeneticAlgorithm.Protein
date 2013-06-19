                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include "algorithm.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

Algorithm::Algorithm(sf::RenderWindow &window) : m_RenderWindow(window), m_DrawConformation(NULL), m_Energy(0), m_Population(NULL)
{
	srand(time(NULL));
}

Algorithm::~Algorithm()
{
	delete m_DrawConformation;
}

void Algorithm::draw()
{
	int offset = ElementRenderer::m_Offset;
	int size = ElementRenderer::m_Size;

	if (!m_DrawConformation) return;

	std::vector<Element> elements = m_DrawConformation->getElements();

	sf::RectangleShape connectionLine(sf::Vector2f(size, 2));
	connectionLine.setFillColor(sf::Color::White);
	connectionLine.setPosition(20, offset + size / 2);

	ScreenDirection direction = ScreenDirection::East;

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		// Map relative direction to screen direction
		direction = calculateDirection(direction, elements[i].getDirection());
		sf::Vector2i position = elements[i].getRenderer().getPosition();

		switch (direction)
		{
			case West:
				connectionLine.setPosition(position.x - size, position.y + size / 2);
				connectionLine.setSize(sf::Vector2f(size, 2));
				break;
			case East:
				connectionLine.setPosition(position.x + size, position.y + size / 2);
				connectionLine.setSize(sf::Vector2f(size, 2));
				break;
			case North:
				connectionLine.setPosition(position.x + size / 2, position.y - size);
				connectionLine.setSize(sf::Vector2f(2, size));
				break;
			case South:
				connectionLine.setPosition(position.x + size / 2, position.y + size);
				connectionLine.setSize(sf::Vector2f(2, size));
				break;
			default:
				break;
		}

		// Draw connection line, but exclude last element
		if (i != elements.size() - 1) m_RenderWindow.draw(connectionLine);
				
		elements[i].getRenderer().draw(m_RenderWindow);
	}
}

void Algorithm::run(int maxGeneration, std::string &chain, float mutationRate, float crossoverRate)
{
	int generation = 0;
	m_Energy = 0;

	gBestEnergy = 0;
	gAvg = 0;

	// Create logfile
	std::ofstream logfile;
	logfile.open ("average.txt");

	// Creates the population using our protein chain
	Population population(chain, 1000, mutationRate, crossoverRate);
	
	// Create initial conformations by random
	population.createInitialPopulation();
	float avgFitness = population.evaluation();

	// Run through all generations
	while (generation < maxGeneration) 
	{
		generation++;
		population.selection();
		population.crossover();
		population.mutation();

		avgFitness = population.evaluation();
		logfile << generation << "\t" << avgFitness << "\t" << population.getBestEnergy() << "\n";
		std::cout << generation << "\t" << avgFitness << "\t" << population.getBestEnergy() << "\n";

		if (population.getBestEnergy() > m_Energy)
		{
			m_DrawConformation = new Conformation(population.getBestConformation());
			m_Energy = population.getBestEnergy();
			gBestEnergy = m_Energy;
		}
	}

	gAvg = avgFitness;

	logfile.close();
}

void Algorithm::update()
{
	if (m_Generation < m_MaxGeneration)
	{
		m_Generation++;
		m_Population->selection();
		m_Population->crossover();
		m_Population->mutation();

		float avgFitness = m_Population->evaluation();
		m_Logfile << m_Generation << "\t" << avgFitness << "\t" << m_Population->getBestEnergy() << "\n";
		std::cout << m_Generation << "\t" << avgFitness << "\t" << m_Population->getBestEnergy() << "\n";

		if (m_Population->getBestEnergy() >= m_Energy)
		{
			m_DrawConformation = new Conformation(m_Population->getBestConformation());
			m_Energy = m_Population->getBestEnergy();
			gBestEnergy = m_Energy;
		}
	}

	// Algorithm is done, clean up
	else
	{
		m_Logfile.close();
	}
}

void Algorithm::setUp( int maxGeneration, std::string &chain, float mutationRate, float crossoverRate )
{
	gBestEnergy = 0;
	gAvg = 0;
	m_MaxGeneration = maxGeneration;
	
	m_Energy = 0;
	m_Generation = 0;
	m_Chain = chain;
	m_MutationRate = mutationRate;
	m_CrossoverRate = crossoverRate;

	m_Population = new Population(chain, 3000, mutationRate, crossoverRate);
	m_Population->createInitialPopulation();
	float avgFitness = m_Population->evaluation();

	gAvg = avgFitness;
	m_Logfile.open("average.txt");
}
                                                                                                                                                                                 