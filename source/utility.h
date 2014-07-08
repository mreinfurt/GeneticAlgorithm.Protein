#include "element.h"
#pragma once
// This file provides helper functions

// Converts relative directions to screen directions
ScreenDirection calculateDirection(ScreenDirection currDir, Direction elemDir);

// Returns the position of the next cell
sf::Vector2i& calculateNextCell(sf::Vector2i &currentCell, ScreenDirection direction);

// Checks if these 2 elements are sequence neighbours
bool isSequenceNeighbour(Element *lhs, Element *rhs);

// Returns the element at a certain position
Element* getElement(int x, int y, std::vector<std::vector<Element*>> &matrix);