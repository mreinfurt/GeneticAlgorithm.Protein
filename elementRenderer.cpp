#include "elementRenderer.h"
#include "element.h"
int ElementRenderer::m_Offset = 40;
int ElementRenderer::m_Size = 20;

ElementRenderer::ElementRenderer(const Element const *element) : m_Element(element), m_Shape(sf::Vector2f(m_Size, m_Size))
{
	m_Shape.setOutlineColor(sf::Color(128, 128, 128, 255));
	m_Shape.setOutlineThickness(1.0);

	sf::Color fillColor = element->getHydrophile() ? sf::Color::White : sf::Color::Black;
	m_Shape.setFillColor(fillColor);
	m_Position = sf::Vector2i(0, 0);
}
	
void ElementRenderer::update()
{
	m_Shape.setPosition((sf::Vector2f) m_Position);
}

void ElementRenderer::draw(sf::RenderWindow &renderWindow)
{
	renderWindow.draw(m_Shape);
}

sf::Vector2i ElementRenderer::getCoordinates() const
{ 
	sf::Vector2i coordinates(((m_Position.x / m_Offset) - 1), 
							 ((m_Position.y / m_Offset) - 1));
	return coordinates;
}

void ElementRenderer::setPosition(sf::Vector2i &position) 
{ 
	m_Position.x = m_Offset + (position.x * m_Offset);
	m_Position.y = m_Offset + (position.y * m_Offset);
}