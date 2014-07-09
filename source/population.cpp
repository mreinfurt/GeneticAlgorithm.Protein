#include "population.h"
#include "utility.h"
#include <random>

sf::Vector2i& calculateNextCell(sf::Vector2i &currentCell, ScreenDirection direction);
int calculateEnergy(std::vector<Element> &elements, std::vector<std::vector<Element*>> &matrix);
std::vector<std::vector<Element*>> createMatrix(Conformation &conformation);

int overlaps = 0;

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="chain">The chain.</param>
/// <param name="populationSize">Size of the population.</param>
/// <param name="mutationRate">The mutation rate.</param>
/// <param name="crossoverRate">The crossover rate.</param>
/// <param name="selection">The selection.</param>
Population::Population(std::string &chain, int populationSize, float mutationRate, float crossoverRate, Selection *selection) : 
					   m_Chain(chain), 
					   m_PopulationSize(populationSize), 
					   m_MutationRate(mutationRate), 
					   m_CrossoverCount(crossoverRate),
					   m_Selection(selection)
{
	#pragma region Read protein string
	m_Elements.clear();
	int ASCII_Offset = 48;

	for (unsigned int i = 0; i < chain.length(); ++i)	
	{
		bool hydrophobe = static_cast<bool> (chain.at(i) - ASCII_Offset);
		Element element(!hydrophobe, i);
		m_Elements.push_back(element);
	}
	#pragma endregion

	m_CumulativeEnergy = 0;
	m_BestEnergy = 0;
	m_CrossoverRate = 1.0f;
}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
Population::~Population()
{
	delete m_Selection;
}

/// <summary>
/// Creates the initial population.
/// </summary>
void Population::createInitialPopulation()
{
	// Create 'n' random conformations
	for (int i = 0; i < m_PopulationSize; ++i)
	{
		Conformation conformation(m_Elements);
		
		// Fill conformation with elements and random direction
		for (unsigned int j = 0; j < m_Elements.size(); ++j)
		{
			// Set random direction
			Direction direction = (Direction) ((rand() % 3) + 1);
			conformation.getElements()[j].setDirection(direction);
		}
		
		m_Conformations.push_back(conformation);
	}
}

/// <summary>
/// Executes the selection for the next generation by using the selection strategy that has been set up.
/// </summary>
void Population::selection()
{	
	m_Selection->select(m_Conformations);
	m_Conformations[0] = *m_BestConformation;
}

/// <summary>
/// Mutates as many elements as given through the m_MutationRate.
/// </summary>
void Population::mutation()
{
	// How many conformations to mutate?
	int NumberToMutate = static_cast<int> (m_PopulationSize * m_MutationRate);

	// Select 'n' conformations and mutate them
	for (int i = 0; i < NumberToMutate; ++i)
	{
		int conformation = rand() % m_PopulationSize;
		m_Conformations[conformation].mutate();
	}
}

/// <summary>
/// Selects conformations and crossovers them.
/// </summary>
void Population::crossover()
{
	// Random number to decide if we have to crossover
	int random = rand() % 100;
	int NumberToCrossover = static_cast<int> (m_PopulationSize * m_CrossoverCount);

	// Crossover?
	if (random < (m_CrossoverRate * 100)) {
		for (int counts = 0; counts < NumberToCrossover; ++counts)
		{
			int conformation = rand() % m_PopulationSize;
			int crossConformation = rand() % m_PopulationSize;
	
			// Conformation gets crossed with crossConformation
			m_Conformations[conformation].crossover(m_Conformations[crossConformation]);
		}
	}
}

/// <summary>
/// Calculates the energy for each conformation.
/// </summary>
/// <returns></returns>
float Population::evaluation()
{
	m_CumulativeEnergy = 0;
	m_BestEnergy = 0;

	// For each conformation
	for (unsigned int i = 0; i < m_Conformations.size(); ++i)
	{
		if (m_Conformations[i].hasChanged()) {
			std::vector<Element> &elements = m_Conformations[i].getElements();
			std::vector<std::vector<Element*>> matrix = createMatrix(m_Conformations[i]);

			// Calculate energy using matrix and list
			int energy = calculateEnergy(elements, matrix);

			// We need to subtract all the overlapping elements to get a good value
			// energy -= (overlaps);
			energy /= (overlaps + 1);

			// Still, energy should not be negative
			if (energy < 0) energy = 0;
			m_Conformations[i].setEnergy(energy);
		}

		// Is this the highest energy value in this population?
		if (m_Conformations[i].getEnergy() > m_BestEnergy)
		{
			m_BestEnergy = m_Conformations[i].getEnergy();
			m_BestConformation = &m_Conformations[i];
		}

		m_CumulativeEnergy += m_Conformations[i].getEnergy();
		m_Conformations[i].setHasChanged(false);
	}

	// Return average fitness
	return m_CumulativeEnergy / (float)m_PopulationSize;
}

/// <summary>
/// Returns the conformation with the highest energy value.
/// </summary>
/// <returns></returns>
const Conformation& Population::getBestConformation() 
{
	return *m_BestConformation;
}

/// <summary>
/// Calculates the energy of the given conformation
/// </summary>
/// <param name="elements">The elements.</param>
/// <param name="matrix">The matrix.</param>
/// <returns></returns>
int calculateEnergy(std::vector<Element> &elements, std::vector<std::vector<Element*>> &matrix) 
{
	int energy = 0;

	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		if (elements[i].isHydrophobe())
		{
			sf::Vector2i coordinates = elements[i].getCoordinates();
			Element *element = &elements[i];
			Element *adjacentElement = NULL;

			// Check right
			if (adjacentElement = getElement(coordinates.x + 1, coordinates.y, matrix))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}

			// Check left
			if (adjacentElement = getElement(coordinates.x - 1, coordinates.y, matrix))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}
			
			// Check bottom
			if (adjacentElement = getElement(coordinates.x, coordinates.y + 1, matrix))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}

			// Check top
			if (adjacentElement = getElement(coordinates.x, coordinates.y - 1, matrix))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}
		}
	}

	// All neighbors are counted twice
	energy /= 2;
	return energy;	
}

/// <summary>
/// Creates the matrix used for calculating the energy.
/// </summary>
/// <param name="conformation">The conformation.</param>
/// <returns></returns>
std::vector<std::vector<Element*>> createMatrix(Conformation &conformation)
{
	std::vector<Element> &elements = conformation.getElements();
	std::vector<ScreenDirection> directions(elements.size());

	#pragma region BoundingBox
		// Create BoundingBox
		int left = 0;
		int right = 0;
		int top = 0;
		int bottom = 0;
		int x = 0;
		int y = 0;

		ScreenDirection currDir = ScreenDirection::East;
		for (unsigned int e = 0; e < elements.size(); ++e)
		{
			Direction elemDir = elements[e].getDirection();		
			directions[e] = currDir = calculateDirection(currDir, elemDir);		

			switch (currDir)
			{
			case North:
				y--;
				if (y < top)
				{
					top--;
				}

				break;

			case South:
				y++;
				if (y > bottom)
				{
					bottom++;
				}

				break;

			case East:
				x++;
				if (x > right)
				{
					right++;
				}
				break;

			case West:
				x--;
				if (x < left)
				{
					left--;
				}
				break;

			default:
				break;
			}
		}

		int width = (-left) + right + 3;
		int height = (-top) + bottom + 3;
	#pragma endregion

	// Create matrix using the bounding box
	std::vector<std::vector<Element*>> matrix;
	matrix.resize(height, std::vector<Element*>(width, NULL));

	// Zero point
	sf::Vector2i position((-left) + 1, (-top) + 1);
	overlaps = 0;

	ScreenDirection direction = ScreenDirection::East;

	// Fill matrix
	for (unsigned int e = 0; e < elements.size(); ++e)
	{
		// Is overlapping?
		if (matrix[position.y][position.x] != NULL) 
		{
			overlaps++;
		}

		matrix[position.y][position.x] = &elements[e];
		matrix[position.y][position.x]->setPosition(position);

		direction = directions[e];
		//direction = calculateDirection(direction, elements[e].getDirection());
		position = calculateNextCell(position, direction);
	}

	return matrix;
}