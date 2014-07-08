#include "conformation.h"
#include "element.h"

Conformation::Conformation(std::vector<Element> &elements) : m_Changed(true)
{
	// Copy all elements
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		m_Elements.push_back(elements[i]);
	}
}

void Conformation::mutate()
{
	// Select a random element
	int element = (rand() % m_Elements.size());

	// Mutate the direction
	Direction direction = m_Elements[element].getDirection();
	int randomDirection = (rand() % 3) + 1;

	// Only setDirection if 
	// (a) it's a new direction
	// (b) direction is not NULL
	while (direction == randomDirection || randomDirection == Direction::None)
	{
		randomDirection = (rand() % 3) + 1;
	}

	m_Elements[element].setDirection((Direction)randomDirection);
	m_Changed = true;
}

void Conformation::crossover(Conformation &conformation)
{
	// Select a random start element
	int startElement = rand() % m_Elements.size();

	// Swap all elements till the end
	for (unsigned int i = startElement; i < m_Elements.size(); ++i)
	{
		//std::swap(m_Elements[i], conformation.m_Elements[i]);
		Direction temp = m_Elements[i].getDirection();

		m_Elements[i].setDirection(conformation.m_Elements[i].getDirection());
		conformation.m_Elements[i].setDirection(temp);
	}

	conformation.setHasChanged(true);
	m_Changed = true;
}