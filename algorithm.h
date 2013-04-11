#include "element.h"
#include "elementRenderer.h"

#include <array>

class Algorithm {
	public:
		Algorithm(sf::RenderWindow &renderWindow);
		void start();
		void draw();

		void fillArrayRandom();

	private:
		std::array<std::array<Element*, 10>, 10> m_Array;
		std::vector<Element> m_Elements;
		sf::RenderWindow &m_RenderWindow;

		// Helper functions
		bool isDirectionPossible(sf::Vector2i position, Element *element);
		sf::Vector2i calculateNextCell(sf::Vector2i &currentCell, Direction *direction);
};