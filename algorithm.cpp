#include "algorithm.h"
#include <time.h>
#include <stdlib.h>

Algorithm::Algorithm(sf::RenderWindow &window) : m_RenderWindow(window)
{
	srand (time(NULL));
	// Fill random proteins
	for (int i = 0; i <= 10; ++i)
	{
		bool hydrophile = rand() % 2;
		Element element(hydrophile, i);
		m_Elements.push_back(element);
	}

	// Initialize array
	for (int y = 0; y < m_Array.size(); ++y)
	{
		for (int x = 0; x < m_Array.size(); ++x)
		{
			m_Array[y][x] = NULL;
		}
	}
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

void Algorithm::fillArrayRandom()
{
	sf::Vector2i currentCell(0, 0);
	bool reachedEnd = false;
	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		m_Array[currentCell.y][currentCell.x] = &m_Elements[i];
		m_Array[currentCell.y][currentCell.x]->getRenderer().setPosition(currentCell);

		Direction direction = (Direction) (rand() % 4);
		currentCell = calculateNextCell(currentCell, &direction);

		m_Elements[i].setDirection(direction);
	}
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

		if (isDirectionPossible(nextCell, m_Array[currentCell.y][currentCell.x]))
		{
			currentCell = nextCell;
			return currentCell;
		}

		int randomDirection = 0 + (rand() % (int)(3 - 0 + 1));
		*direction = (Direction)randomDirection;
		calculateNextCell(currentCell, direction);
}

bool Algorithm::isDirectionPossible(sf::Vector2i position, Element *element) 
{
	sf::Vector2i coordinates = element->getRenderer().getCoordinates();
	
	// X position out of bounds
	if (!(position.x >= 0 && position.x <= m_Array.size()))
	{
		return false;
	}

	// Y position out of bounds
	if (!(position.y >= 0 && position.y <= m_Array.size()))
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