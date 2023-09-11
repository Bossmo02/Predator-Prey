#pragma once

#include "Cell.h"
#include <vector>
#include <chrono>
#include <sstream>

enum class DIRECTION
{
	NORTH = 0,
	WEST,
	SOUTH,
	EAST
};

class App
{

public:
	App(uint32_t cellSize, sf::Vector2f windowSize);
	App(uint32_t cellSize, sf::Vector2f windowSize, uint32_t preyStartCount, uint32_t predatorStartCount);
	~App();

	void update();
	void updateCreatures();
	void handleEvents();

	void render();


private:

	void updatePrey(Creature & thisCreature, Creature & otherCreature);
	void updatePredator(Creature& thisCreature, Creature& otherCreature);

	std::chrono::milliseconds getTime();

	const int getCellIndex(size_t x, size_t y);

	unsigned int m_worldWidht;
	unsigned int m_worldHeight;
	unsigned short m_stepTime = 10;
	std::chrono::milliseconds m_startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	bool m_running = true;

	std::auto_ptr<sf::RenderWindow> m_window;

	std::vector<Cell> m_cells;

	long m_preyCount = 0;
	long m_predatorCount = 0;

	sf::Font m_font;
	sf::Text m_text;
};

