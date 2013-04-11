#include "elementRenderer.h"
#include "element.h"
int ElementRenderer::m_Offset = 40;
int ElementRenderer::m_Size = 20;

ElementRenderer::ElementRenderer(const Element const *element) : m_Element(element), m_Shape(sf::Vector2f(m_Size, m_Size))
{
	m_Shape.setOutlineColor(sf::Color::Black);
	m_Shape.setOutlineThickness(1.0);
	if (element->getHydrophile() == true)
	{
		m_Shape.setFillColor(sf::Color::Black);
	}
	else
	{
		m_Shape.setFillColor(sf::Color::White);
	}
}
	
void ElementRenderer::update()
{
	m_Shape.setPosition((sf::Vector2f) m_Position);
}

void ElementRenderer::draw(sf::RenderWindow &renderWindow)
{
	renderWindow.draw(m_Shape);
}