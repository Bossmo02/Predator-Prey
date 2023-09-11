#include "Cell.h"



Cell::Cell(unsigned int x, unsigned int y, float cellSize)
{
	addQuad(x, y, cellSize);
	update();
}

Creature& Cell::getCreature()
{
	return m_creature;
}

void Cell::setColor(sf::Color col)
{
	m_vertexArr[0].color = col;
	m_vertexArr[1].color = col;
	m_vertexArr[2].color = col;
	m_vertexArr[3].color = col;
}

void Cell::update()
{
	switch (m_creature.getCreatureType())
	{
	case CREATURE_TYPE::NOTHING:
		setColor(sf::Color::Black);
		break;
	case CREATURE_TYPE::PREY:
		setColor(sf::Color::Green);
		break;
	case CREATURE_TYPE::PREDATOR:
		setColor(sf::Color::Red);
		break;
	}

	m_creature.update();
}

void Cell::render(sf::RenderTarget& target)
{
	target.draw(m_vertexArr.data(), m_vertexArr.size(), sf::PrimitiveType::Quads);
}

void Cell::addQuad(unsigned int x, unsigned int y, float cellSize)
{

	sf::Vertex topLeft;
	sf::Vertex topRight;
	sf::Vertex bottomLeft;
	sf::Vertex bottomRight;

	topLeft.color = sf::Color::Black;
	topRight.color = sf::Color::Black;
	bottomLeft.color = sf::Color::Black;
	bottomRight.color = sf::Color::Black;

	topLeft.position = sf::Vector2f(x, y);
	topRight.position = sf::Vector2f(x + cellSize, y);
	bottomLeft.position = sf::Vector2f(x, y + cellSize);
	bottomRight.position = sf::Vector2f(x + cellSize, y + cellSize);

	m_vertexArr[0] = topLeft;
	m_vertexArr[1] = topRight;
	m_vertexArr[2] = bottomRight;
	m_vertexArr[3] = bottomLeft;
}