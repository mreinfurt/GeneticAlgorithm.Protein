#include "element.h"

Element::Element(bool hydrophile, int index) : m_Renderer(this), m_Hydrophile(hydrophile), m_Index(index), m_Direction(East) {
}