#include "Guess.h"

Guess::Guess(std::vector<colors> theGuess):
m_combination(theGuess)
{
}

std::vector<colors> Guess::getCombination()
{
	return m_combination;
}

void Guess::calculateHint(std::vector<colors> code)
{
	std::vector<colors> codeCopy(code);
	std::vector<colors> combinationCopy(m_combination);
	int numOfBlack = 0;
	int numOfWhite = 0;
	//first loop : set num of black (right color right place).
	//for a color we already used, change in codeCopy and combination to 0 (NA).
	for (unsigned int i = 0; i < codeCopy.size(); ++i)
	{
		if (combinationCopy[i] == codeCopy[i])
		{
			++numOfBlack;
			codeCopy[i] = NA;
			combinationCopy[i] = NA;

		}
	}
	//second loop: check for "white": saame color, different location.

	for (unsigned int i = 0; i < codeCopy.size(); ++i)
	{
		if (combinationCopy[i] != NA)
		{
			for (unsigned int j = 0; j < codeCopy.size(); ++j)
			{
				if (codeCopy[j] == NA)
				{
					if (combinationCopy[i] == codeCopy[j])
					{
						++numOfWhite;
						codeCopy[j] = NA;
					}
				}
			}
		}
	}
	int i = 0;
	while (numOfBlack != 0)
	{
		m_hint[i] = black;
		++i;
		--numOfBlack;
	}
	while (numOfWhite != 0)
	{
		m_hint[i] = white;
		++i;
		--numOfWhite;
	}
	return;

}

std::vector<hints> Guess::getHint()
{
	return m_hint;
}
