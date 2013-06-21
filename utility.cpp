#include "utility.h"

ScreenDirection calculateDirection(ScreenDirection currDir, Direction elemDir)
{
	bool LE = (currDir == East && elemDir == Left);
	bool SN = (currDir == North && elemDir == Straight);
	bool RW = (currDir == West && elemDir == Right);

	bool SE = (currDir == East && elemDir == Straight);
	bool LS = (currDir == South && elemDir == Left);
	bool RN = (currDir == North && elemDir == Right);

	bool SS = (currDir == South && elemDir == Straight);
	bool LW = (currDir == West && elemDir == Left);
	bool RE = (currDir == East && elemDir == Right);

	bool SW = (currDir == West && elemDir == Straight);
	bool LN = (currDir == North && elemDir == Left);
	bool RS = (currDir == South && elemDir == Right);

	// North
	if (LE || SN || RW)
		return ScreenDirection::North;

	// South
	else if (SS || LW || RE)
		return ScreenDirection::South;

	// East
	else if (SE || LS || RN)
		return ScreenDirection::East;

	// West
	else // if (SW || LN || RS)
		return ScreenDirection::West;
}

sf::Vector2i& calculateNextCell(sf::Vector2i &currentCell, ScreenDirection direction)
{
	sf::Vector2i &nextCell = currentCell;
	switch (direction)
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

bool isSequenceNeighbour(Element *lhs, Element *rhs)
{
	return (lhs->getIndex() == rhs->getIndex() - 1 || lhs->getIndex() == rhs->getIndex() + 1);
}

Element* getElement(int x, int y, std::vector<std::vector<Element*>> &matrix)
{
	return matrix[y][x];
}