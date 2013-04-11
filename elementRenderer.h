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
		void setPosition(sf::Vector2i &position);

		sf::Vector2i getCoordinates() const;

	private:
		const Element *m_Element;
		sf::RectangleShape m_Shape;
		sf::Sprite m_Sprite;
		sf::Vector2i m_Position;
};