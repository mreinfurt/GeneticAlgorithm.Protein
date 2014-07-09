#include "element.h"

int Element::Offset = 40;
float Element::Size = 20;

/// <summary>
/// Initializes a new instance of the <see cref=""/> .
/// </summary>
/// <param name="hydrophile">if set to <c>true</c> [hydrophile].</param>
/// <param name="index">The index.</param>
Element::Element(bool hydrophile, int index) : m_Hydrophile(hydrophile), m_Index(index), m_Direction(None) {
}

/// <summary>
/// Get screen coordinates.
/// </summary>
/// <returns></returns>
sf::Vector2i Element::getCoordinates() const
{ 
	sf::Vector2i coordinates(((m_Position.x / Offset) - 1), 
		((m_Position.y / Offset) - 1));
	return coordinates;
}

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void Element::setPosition(sf::Vector2i &position) 
{ 
	m_Position.x = Offset + (position.x * Offset);
	m_Position.y = Offset + (position.y * Offset);
}

/// <summary>
/// Returns the position.
/// </summary>
/// <returns></returns>
sf::Vector2i& Element::getPosition()
{
	return m_Position;
}