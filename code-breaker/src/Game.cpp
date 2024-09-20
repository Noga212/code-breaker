#include "Game.h"

Game::Game(): m_result(0),m_codeSize(4)
{
	std::random_device randomizer;
	std::mt19937 generator(randomizer());
	std::uniform_int_distribution<> distribution(1, 6);
	for (int i = 0; i < m_codeSize; ++i)
	{
		colors randomColor = static_cast<colors>(distribution(generator));
		m_code[i] = randomColor;

	}

}

int Game::getResult()
{
	return m_result;
}
