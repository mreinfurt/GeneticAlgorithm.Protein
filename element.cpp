#include "element.h"

int Element::m_Offset = 40;
int Element::m_Size = 20;

Element::Element(bool hydrophile, int index) : m_Hydrophile(hydrophile), m_Index(index), m_Direction(None) {
}

sf::Vector2i Element::getCoordinates() const
{ 
	sf::Vector2i coordinates(((m_Position.x / m_Offset) - 1), 
		((m_Position.y / m_Offset) - 1));
	return coordinates;
}

void Element::setPosition(sf::Vector2i &position) 
{ 
	m_Position.x = m_Offset + (position.x * m_Offset);
	m_Position.y = m_Offset + (position.y * m_Offset);
}

sf::Vector2i& Element::getPosition()
{
	return m_Position;
}