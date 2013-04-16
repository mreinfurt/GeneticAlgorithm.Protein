#include "element.h"
#include "elementRenderer.h"
#include <array>
#include <string>

class Algorithm {
	public:
		Algorithm(sf::RenderWindow &renderWindow);

		void draw();

		void readProteinsFromString(const std::string &proteins);
		Element* getElement(int x, int y);
		int getEnergy() { return m_Energy; }

		void foldRandom();

	private:
		// Data
		std::array<std::array<Element*, 13>, 13> m_Array;
		std::vector<Element> m_Elements;
		int m_Energy;

		int calculateEnergy();
		int calculateEnergy(std::vector<Element> folding);
		// Render
		sf::RenderWindow &m_RenderWindow;

		// Helper functions
		void resetArray();
		bool isDirectionPossible(sf::Vector2i position);
		sf::Vector2i calculateNextCell(sf::Vector2i &currentCell, Direction *direction);
		bool Algorithm::isSequenceNeighbour(Element *lhs, Element *rhs);
};