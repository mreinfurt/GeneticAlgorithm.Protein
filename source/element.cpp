#include "element.h"

int Element::Offset = 40;
float Element::Size = 20;

Element::Element(bool hydrophile, int index) : m_Hydrophile(hydrophile), m_Index(index), m_Direction(None) {
}

sf::Vector2i Element::getCoordinates() const
{ 
	sf::Vector2i coordinates(((m_Position.x / Offset) - 1), 
		((m_Position.y / Offset) - 1));
	return coordinates;
}

void Element::setPosition(sf::Vector2i &position) 
{ 
	m_Position.x = Offset + (position.x * Offset);
	m_Position.y = Offset + (position.y * Offset);
}

sf::Vector2i& Element::getPosition()
{
	return m_Position;
}