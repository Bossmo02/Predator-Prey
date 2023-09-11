#include "Random.h"

#include <time.h>

Random & Random::get()
{
	static Random r;
	return r;
}

int Random::getIntInRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);

	return dist(m_gen);
}

float Random::getFloatInRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);

	return dist(m_gen);
}

Random::Random()
{
	m_gen.seed((unsigned int)time(nullptr));
}

