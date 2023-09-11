#pragma once

#include <random>

class Random
{
public:
	
	static Random & get();

	int getIntInRange(int min, int max);
	float getFloatInRange(float min, float max);

private:

	Random();

	std::mt19937 m_gen;

};

