#pragma once
#include <SFML/Graphics.hpp>

class Element;
class ElementRenderer
{
	public:
		static int m_Offset;
		static int m_Size;
		ElementRenderer(const Element const *element);
		void update();
		void draw(sf::RenderWindow &renderWindow);
		sf::Vector2i& getPosition() { return m_Position; }

		sf::Vector2i getCoordinates() { 
			sf::Vector2i coordinates(((m_Position.x / m_Offset) - 1), 
									 ((m_Position.y / m_Offset) - 1));
			return coordinates;
		}

		void setPosition(sf::Vector2i &position) 
		{ 
			m_Position.x = m_Offset + (position.x * m_Offset);
			m_Position.y = m_Offset + (position.y * m_Offset);
		}

	private:
		const Element *m_Element;
		sf::RectangleShape m_Shape;
		sf::Sprite m_Sprite;
		sf::Vector2i m_Position;
};