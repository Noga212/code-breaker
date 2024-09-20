#include "Game.h"


Game::Game(): m_codeSize(4)
{
	std::random_device randomizer;
	std::mt19937 generator(randomizer());
	std::uniform_int_distribution<> distribution(1, 6);

	for (int i = 0; i < m_codeSize; ++i)
	{
		m_code.push_back(static_cast<colors>(distribution(generator)));
	}

}


