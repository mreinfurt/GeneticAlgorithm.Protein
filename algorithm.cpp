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
	int offset = Element::Offset;
	float size = Element::Size;

	sf::RectangleShape m_Shape(sf::Vector2f(size, size));
	m_Shape.setOutlineColor(sf::Color(128, 128, 128, 255));
	m_Shape.setOutlineThickness(1.0);

	if (!m_DrawConformation) return;

	std::vector<Element> elements = m_DrawConformation->getElements();

	sf::RectangleShape connectionLine(sf::Vector2f(size, 2.0f));
	connectionLine.setFillColor(sf::Color::White);
	connectionLine.setPosition(20, offset + size / 2);

	ScreenDirection direction = ScreenDirection::East;

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		// Map relative direction to screen direction
		direction = calculateDirection(direction, elements[i].getDirection());
		sf::Vector2i position = elements[i].getPosition();

		sf::Color fillColor = elements[i].isHydrophile() ? sf::Color::White : sf::Color::Black;
		m_Shape.setFillColor(fillColor);

		switch (direction)
		{
			case West:
				connectionLine.setPosition(position.x - size, position.y + size / 2.0f);
				connectionLine.setSize(sf::Vector2f(size, 2.0f));
				break;
			case East:
				connectionLine.setPosition(position.x + size, position.y + size / 2.0f);
				connectionLine.setSize(sf::Vector2f(size, 2.0f));
				break;
			case North:
				connectionLine.setPosition(position.x + size / 2.0f, position.y - size);
				connectionLine.setSize(sf::Vector2f(2.0f, size));
				break;
			case South:
				connectionLine.setPosition(position.x + size / 2.0f, position.y + size);
				connectionLine.setSize(sf::Vector2f(2.0f, size));
				break;
			default:
				break;
		}

		// Draw connection line, but exclude last element
		if (i != elements.size() - 1) m_RenderWindow.draw(connectionLine);

		m_Shape.setPosition((sf::Vector2f) elements[i].getPosition());
		m_RenderWindow.draw(m_Shape);
		//elements[i].getRenderer().draw(m_RenderWindow);
	}
}


void Algorithm::run(bool output)
{
	float avgFitness = m_Population->evaluation();

	// Run through all generations
	while (m_Generation < m_MaxGeneration) 
	{
		m_Generation++;
		m_Population->selection();
		m_Population->crossover();
		m_Population->mutation();

		avgFitness = m_Population->evaluation();
		if (output) 
		{
			m_Logfile << m_Generation << "\t" << avgFitness << "\t" << m_Population->getBestEnergy() << "\n";
			std::cout << m_Generation << "\t" << avgFitness << "\t" << m_Population->getBestEnergy() << "\n";
		}

		if (m_Population->getBestEnergy() >= m_Energy)
		{
			m_DrawConformation = new Conformation(m_Population->getBestConformation());
			m_Energy = m_Population->getBestEnergy();
			m_BestEnergy = m_Energy;
		}
	}

	m_AverageFitness = avgFitness;
	m_Logfile.close();
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
			m_BestEnergy = m_Energy;
		}
	}

	// Algorithm is done, clean up
	else
	{
		m_Logfile.close();
	}
}

void Algorithm::setUp(int maxGeneration, int populationSize, std::string &chain, float mutationRate, float crossoverRate, Selection *selection, std::string &file)
{
	m_Energy = 0;
	m_BestEnergy = 0;
	m_AverageFitness = 0;
	m_MaxGeneration = maxGeneration;

	m_Generation = 0;
	m_Chain = chain;
	m_MutationRate = mutationRate;
	m_CrossoverRate = crossoverRate;

	m_Population = new Population(chain, populationSize, mutationRate, crossoverRate, selection);
	m_Population->createInitialPopulation();
	float avgFitness = m_Population->evaluation();

	m_AverageFitness = avgFitness;
	m_Logfile.open(file);
}
