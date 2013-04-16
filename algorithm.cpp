#include "algorithm.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

Algorithm::Algorithm(sf::RenderWindow &window) : m_RenderWindow(window)
{
	srand (time(NULL));
	m_Energy = -1;

	// Fill random proteins
	for (int i = 0; i <= 10; ++i)
	{
		bool hydrophile = rand() % 2;
		Element element(hydrophile, i);
		m_Elements.push_back(element);
	}

	// Initialize array
	resetArray();
}

void Algorithm::draw()
{
	int offset = ElementRenderer::m_Offset;
	int size = ElementRenderer::m_Size;

	sf::RectangleShape connectionLine(sf::Vector2f(size, 2));
	connectionLine.setFillColor(sf::Color::White);
	connectionLine.setPosition(20, offset + size / 2);

	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		Direction direction = m_Elements[i].getDirection();
		sf::Vector2i position = m_Elements[i].getRenderer().getPosition();

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
		if (i != m_Elements.size() - 1) m_RenderWindow.draw(connectionLine);
				
		m_Elements[i].getRenderer().update();
		m_Elements[i].getRenderer().draw(m_RenderWindow);
	}
}

void Algorithm::resetArray()
{
	for (int y = 0; y < m_Array.size(); ++y)
	{
		for (int x = 0; x < m_Array.size(); ++x)
		{
			m_Array[y][x] = NULL;
		}
	}
}

void Algorithm::foldRandom()
{
	resetArray();

	bool possible = true;
	sf::Vector2i currentCell(7, 7);
	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		m_Array[currentCell.y][currentCell.x] = &m_Elements[i];
		m_Array[currentCell.y][currentCell.x]->getRenderer().setPosition(currentCell);

		Direction direction = (Direction) (rand() % 4);
		sf::Vector2i nextCell = currentCell;
		nextCell = calculateNextCell(currentCell, &direction);
		
		int counter = 0;

		while (!isDirectionPossible(nextCell) && counter < 10)
		{
			direction = (Direction) (rand() % 4);
			nextCell = calculateNextCell(currentCell, &direction);

			counter++;
		}

		if (counter >= 10)
		{
			possible = false;
			break;
		}

		currentCell = nextCell;
		m_Elements[i].setDirection(direction);
	}

	if (!possible) foldRandom();
	std::cout << this->calculateEnergy();
}

sf::Vector2i Algorithm::calculateNextCell(sf::Vector2i &currentCell, Direction *direction)
{
		sf::Vector2i nextCell = currentCell;
		switch (*direction)
		{
		case North:
			nextCell.y -= 1;
			break;
		case South:
			nextCell.y += 1;
			break;
		case West:
			nextCell.x -= 1;
			break;
		case East:
			nextCell.x += 1;
			break;
		default:
			break;
		}

		return nextCell;
}

bool Algorithm::isDirectionPossible(sf::Vector2i position) 
{	
	// X position out of bounds
	if (!(position.x >= 0 && position.x < m_Array.size()))
	{
		return false;
	}

	// Y position out of bounds
	if (!(position.y >= 0 && position.y < m_Array.size()))
	{
		return false;
	}

	// Cell is already occupied
	if (m_Array[position.y][position.x] != NULL)
	{
		return false;
	}

	// No problems occured, direction is possible
	return true;
}

void Algorithm::readProteinsFromString(const std::string &proteins)
{
	m_Elements.clear();
	int ASCII_Offset = 48;

	for (int i = 0; i < proteins.length(); ++i)
	{
		bool hydrophobe = (bool) (proteins.at(i) - ASCII_Offset);
		Element element(!hydrophobe, i);
		m_Elements.push_back(element);
	}
}

Element* Algorithm::getElement(int x, int y)
{
	if ((x >= 0 && x < m_Array.size()) && 
		(y >= 0 && y < m_Array.size()))
	{
		return m_Array[y][x];
	}
	else
	{
		return NULL;
	}
}

int Algorithm::calculateEnergy(std::vector<Element> folding) {
	int energy = 0;

	for (int i = 0; i < m_Elements.size(); ++i)
	{
		if (m_Elements[i].isHydrophobe())
		{
			sf::Vector2i coordinates = m_Elements[i].getRenderer().getCoordinates();
			Element *element = &m_Elements[i];
			Element *adjacentElement = NULL;

			// Check overlapping elements

		
			// Check right
			if (adjacentElement = getElement(coordinates.x + 1, coordinates.y))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}

			// Check left
			if (adjacentElement = getElement(coordinates.x - 1, coordinates.y))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}

			// Check bottom
			if (adjacentElement = getElement(coordinates.x, coordinates.y + 1))
			{
				if (!isSequenceNeighbour(element, adjacentElement) && adjacentElement->isHydrophobe())
				{
					energy++;
				}
			}

			// Check top
			if (adjacentElement = getElement(coordinates.x, coordinates.y - 1))
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
	m_Energy = energy;
	return m_Energy;	
}

int Algorithm::calculateEnergy()
{
	return calculateEnergy();
}

bool Algorithm::isSequenceNeighbour(Element *lhs, Element *rhs)
{
	return (lhs->getIndex() == rhs->getIndex() - 1 || lhs->getIndex() == rhs->getIndex() + 1);
}