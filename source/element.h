#pragma once
#include <SFML\Graphics.hpp>

/// <summary>
/// The translated direction for the screen
/// </summary>
enum ScreenDirection {
	North,
	South,
	West,
	East
};

/// <summary>
/// The possible directions a single element can have.
/// </summary>
enum Direction {
	None,
	Left,
	Right,
	Straight
};

/// <summary>
/// Represents one element of the protein chain, identified by it's index.
/// </summary>
class Element {
	public:
		// Ctor
		Element(bool hydrophile, int index);

		// Returns wheter or not the element is hydrophile/hydrophobe
		bool isHydrophile() const { return m_Hydrophile; }
		bool isHydrophobe() const { return !m_Hydrophile; };

		// Returns the direction the element is facing towards
		Direction getDirection() const { return m_Direction; }
		void setDirection(Direction direction) { m_Direction = direction; }

		// Returns the index (= position) in the sequence
		int getIndex() { return m_Index; }

		// Returns the physical (= screen) position
		sf::Vector2i& getPosition();
		void setPosition(sf::Vector2i &position);

		// Returns the coordinates in the matrix
		sf::Vector2i getCoordinates() const;

		// Physical dimensions of an element
		static int Offset;
		static float Size;

	private:
		bool m_Hydrophile;
		int m_Index;
		Direction m_Direction;		
		sf::Vector2i m_Position;
};