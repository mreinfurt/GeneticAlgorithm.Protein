#pragma once
#include <SFML\Graphics.hpp>

enum ScreenDirection {
	North,
	South,
	West,
	East
};

enum Direction {
	None,
	Left,
	Right,
	Straight
};

/// Element
/// Represents one element of the protein chain, identified by it's index
class Element {
	public:
		Element(bool hydrophile, int index);

		bool getHydrophile() const { return m_Hydrophile; }
		bool isHydrophobe() const { return !m_Hydrophile; };

		Direction getDirection() const { return m_Direction; }
		void setDirection(Direction direction) { m_Direction = direction; }

		int getIndex() { return m_Index; }

		sf::Vector2i& getPosition();
		void setPosition(sf::Vector2i &position);

		sf::Vector2i getCoordinates() const;

		static int m_Offset;
		static int m_Size;

	private:
		bool m_Hydrophile;
		int m_Index;
		Direction m_Direction;		
		sf::Vector2i m_Position;
};