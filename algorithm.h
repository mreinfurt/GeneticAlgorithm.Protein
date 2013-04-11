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
		Element* getElement(int x, int y);
		int getEnergy() { return m_Energy; }

		void foldRandom();

	private:
		// Data
		std::array<std::array<Element*, 13>, 13> m_Array;
		std::vector<Element> m_Elements;
		int m_Energy;

		// Render
		sf::RenderWindow &m_RenderWindow;

		// 
		int calculateEnergy();

		// Helper functions
		bool isDirectionPossible(sf::Vector2i position);
		sf::Vector2i calculateNextCell(sf::Vector2i &currentCell, Direction *direction);
		bool Algorithm::isSequenceNeighbour(Element *lhs, Element *rhs);
};