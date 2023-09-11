#pragma once
#include "SFML/Graphics.hpp"
#include "Random.h"

enum class CREATURE_TYPE
{
	NOTHING,
	PREY,
	PREDATOR
};

class Creature
{
public:

	constexpr static unsigned int MAX_HEALTH = 100;

	Creature();
	~Creature() = default;

	const CREATURE_TYPE getCreatureType() const;
	const uint8_t getHealth() const;

	void setCreatureType(CREATURE_TYPE type);

	void update();

	void heal(int amount);
	void reproduce(Creature & otherCreature);
	void move(Creature& otherCreature);


private:

	CREATURE_TYPE m_creatureType;
	uint8_t m_health;
};

