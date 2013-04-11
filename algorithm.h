#include "element.h"
#include "elementRenderer.h"
#include <array>
#include <string>

class Algorithm {
	public:
		Algorithm(sf::RenderWindow &renderWindow);

		void start();
		void draw();

		void readProteinsFromString(std::string proteins);

		void fillArrayRandom();

	private:
		// Data
		std::array<std::array<Element*, 10>, 10> m_Array;
		std::vector<Element> m_Elements;

		// Render
		sf::RenderWindow &m_RenderWindow;

		// 
		int calculateEnergy();

		// Helper functions
		bool isDirectionPossible(sf::Vector2i position, Element *element);
		sf::Vector2i calculateNextCell(sf::Vector2i &currentCell, Direction *direction);
};