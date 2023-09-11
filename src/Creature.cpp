#include "Creature.h"

Creature::Creature()
{
	int rand = Random::get().getIntInRange(0, 1000);
	
	if (rand < 1)
	{
		m_creatureType = CREATURE_TYPE::PREDATOR;
	}
	else if (rand < 10)
	{
		m_creatureType = CREATURE_TYPE::PREY;
	}
	else
	{
		m_creatureType = CREATURE_TYPE::NOTHING;
	}

	switch (m_creatureType)
	{
	case CREATURE_TYPE::NOTHING:
		break;
	case CREATURE_TYPE::PREY:
		m_health = MAX_HEALTH / 4;
		break;
	case CREATURE_TYPE::PREDATOR:
		m_health = MAX_HEALTH;
		break;
	default:
		break;
	}
}

const CREATURE_TYPE Creature::getCreatureType() const
{
	return m_creatureType;
}

const uint8_t Creature::getHealth() const
{
	return m_health;
}

void Creature::setCreatureType(CREATURE_TYPE type)
{
	m_creatureType = type;
}

void Creature::update()
{
	switch (m_creatureType)
	{
	case CREATURE_TYPE::PREY:
		heal(1);
		break;
	case CREATURE_TYPE::PREDATOR:
		heal(-1);
		break;
	default:
		break;
	}


}

void Creature::heal(int amount) 
{
	m_health += amount;
}

void Creature::reproduce(Creature & otherCreature)
{
	m_health = MAX_HEALTH / 4;
	otherCreature.m_creatureType = m_creatureType;
	otherCreature.m_health = MAX_HEALTH/4;
}

void Creature::move(Creature & otherCreature)
{
	otherCreature.setCreatureType(m_creatureType);
	otherCreature.m_health = m_health;
	m_creatureType = CREATURE_TYPE::NOTHING;
}

