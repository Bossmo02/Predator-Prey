#pragma once
#include "Creature.h"

#include <array>

class Cell
{
public:

	Cell(unsigned int x, unsigned int y, float cellSize);

	Creature& getCreature();

	void setColor(sf::Color col);

	void update();
	void render(sf::RenderTarget& target);

private:

	void addQuad(unsigned int x, unsigned int y, float cellSize);
	
	std::array<sf::Vertex, 4> m_vertexArr;
	Creature m_creature;
};

