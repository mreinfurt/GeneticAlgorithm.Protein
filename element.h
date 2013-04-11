#pragma once
#include "elementRenderer.h"
enum Direction {
	North,
	South,
	West,
	East
};

class Element {
	public:
		Element(bool hydrophile, int index);

		bool getHydrophile() const { return m_Hydrophile; }

		Direction getDirection() const { return m_Direction; }
		void setDirection(Direction direction) { m_Direction = direction; }

		ElementRenderer& getRenderer() { return m_Renderer; }

	private:
		bool m_Hydrophile;
		int m_Index;
		Direction m_Direction;
		
		ElementRenderer m_Renderer;
};