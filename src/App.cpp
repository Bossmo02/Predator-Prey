#include "App.h"

#include <iostream>

App::App(uint32_t cellSize, sf::Vector2f windowSize)
{
	m_window.reset(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(windowSize.x), static_cast<unsigned int>(windowSize.y)), "Predator and Prey"));

	m_worldWidht = windowSize.x / cellSize;
	m_worldHeight = windowSize.y / cellSize;

	// create cells
	for (size_t y = 0; y < m_worldWidht; ++y)
	{
		for (size_t x = 0; x < m_worldHeight; ++x)
		{
			m_cells.push_back(Cell(x * cellSize, y * cellSize, cellSize));
		}
	}

	m_font.loadFromFile("Humnst777 BlkCn BT Black.ttf");
	
	m_text.setFont(m_font);
	m_text.setPosition(10, 10);
	m_text.setCharacterSize(25);

	for (Cell c : m_cells)
	{
		if (c.getCreature().getCreatureType() == CREATURE_TYPE::PREDATOR)
			m_predatorCount++;
		else if (c.getCreature().getCreatureType() == CREATURE_TYPE::PREY)
			m_preyCount++;
	}

	render();
}

App::App(uint32_t cellSize, sf::Vector2f windowSize, uint32_t preyStartCount, uint32_t predatorStartCount)
{
	m_window.reset(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(windowSize.x), static_cast<unsigned int>(windowSize.y)), "Predator and Prey"));

	m_worldWidht = windowSize.x / cellSize;
	m_worldHeight = windowSize.y / cellSize;

	// create cells
	for (size_t y = 0; y < m_worldWidht; ++y)
	{
		for (size_t x = 0; x < m_worldHeight; ++x)
		{
			m_cells.push_back(Cell(x * cellSize, y * cellSize, cellSize));
		}
	}

	m_font.loadFromFile("Humnst777 BlkCn BT Black.ttf");

	m_text.setFont(m_font);
	m_text.setPosition(10, 10);
	m_text.setCharacterSize(25);

	m_predatorCount = predatorStartCount;
	m_preyCount = preyStartCount;

	render();
}

App::~App()
{
}

void App::update()
{
	while (m_running)
	{
		handleEvents();

		if ((getTime().count() - m_startTime.count()) > m_stepTime)
		{
			updateCreatures();


			m_startTime = getTime();
		}

		render();
	}
}

void App::updateCreatures()
{
	for (size_t x = 0; x < m_worldWidht; ++x)
	{
		for (size_t y = 0; y < m_worldHeight; ++y)
		{
			int index = getCellIndex(x, y);

			Creature& thisCreature = m_cells.at(index).getCreature();

			if (thisCreature.getCreatureType() == CREATURE_TYPE::NOTHING)
			{

			}
			else
			{
				try
				{
					int x2 = x + Random::get().getIntInRange(-1, 1);
					int y2 = y + Random::get().getIntInRange(-1, 1);

					if (x2 < 0 || x2 >= m_worldWidht || y2 < 0 || y2 > m_worldHeight)
					{

					}
					else
					{
						int indexOther = getCellIndex(x2, y2);
						Creature& otherCreature = m_cells[indexOther].getCreature();
						CREATURE_TYPE thisType = thisCreature.getCreatureType();

						if (thisType == CREATURE_TYPE::PREY)
						{
							updatePrey(thisCreature, otherCreature);
						}

						if (thisType == CREATURE_TYPE::PREDATOR)
						{
							updatePredator(thisCreature, otherCreature);
						}

						m_cells[index].update();
						m_cells[indexOther].update();
					}
				}
				catch (std::exception e)
				{
					std::cout << "Exception: " << e.what() << std::endl;
				}
				
			}

		}
	}
}

void App::handleEvents()
{
	sf::Event evnt;
	while (m_window.get()->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			m_window.get()->close();
			m_running = false;
			break;

		default:
			break;
		}
	}
}

void App::render()
{
	m_window.get()->clear(sf::Color::Black);
	
	std::stringstream oss;
	oss << "Prey Count: " << m_preyCount << "\tPredator Count: " << m_predatorCount;
	m_text.setString(oss.str());

	for (uint32_t i = 0; i < m_cells.size(); ++i)
	{
		m_cells.at(i).render(*m_window.get());
	}
	m_window.get()->draw(m_text);
	m_window.get()->display();
}

void App::updatePrey(Creature& thisCreature, Creature& otherCreature)
{
	if (thisCreature.getHealth() >= thisCreature.MAX_HEALTH)
	{
		thisCreature.reproduce(otherCreature);
		m_preyCount++;
	}
	else if(otherCreature.getCreatureType() == CREATURE_TYPE::NOTHING)
	{
		thisCreature.move(otherCreature);
	}
}

void App::updatePredator(Creature& thisCreature, Creature& otherCreature)
{
	if (thisCreature.getHealth() <= 0)
	{
		thisCreature.setCreatureType(CREATURE_TYPE::NOTHING);
		m_predatorCount--;
	}
	else if (otherCreature.getCreatureType() == CREATURE_TYPE::PREY)
	{
		thisCreature.heal(100);
		otherCreature.setCreatureType(CREATURE_TYPE::PREDATOR);
		m_predatorCount++;
		m_preyCount--;
	}
	else if(otherCreature.getCreatureType() == CREATURE_TYPE::NOTHING)
	{
		thisCreature.move(otherCreature);
	}
}

std::chrono::milliseconds App::getTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

const int App::getCellIndex(size_t x, size_t y)
{
	return (x*m_worldWidht) + y;
}
