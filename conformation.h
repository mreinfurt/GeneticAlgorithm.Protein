#pragma once
#include <SFML/Graphics.hpp>
#include "element.h"
#include "utility.h"

// Holds all the directions
class Conformation 
{
public:
	// Ctor
	Conformation(std::vector<Element> &elements);

	// Mutates one random direction of the elements vector
	void mutate();

	// Selects a position and connects this conformation with the new one
	void crossover(Conformation &conformation);

	// Returns the vector of elements
	std::vector<Element>& getElements() { return m_Elements; }

	// Has the conformation changed?
	bool hasChanged() const { return m_Changed; }
	void setHasChanged(bool val) { m_Changed = val; }

	// Returns the current energy of the conformation
	int getEnergy() const { return m_Energy; }
	void setEnergy(int val) { m_Energy = val; }

	bool operator<(const Conformation& rhs)
	{
		return this->getEnergy() < rhs.getEnergy();
	}

private:
	// Chain with directions
	std::vector<Element> m_Elements;

	// Do we need to calculate the energy again?
	bool m_Changed;

	// Energy value of this conformation
	int m_Energy;
};
