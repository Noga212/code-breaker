#pragma once
#include <random>
#include "Guess.h"

class Game
{
public:
	Game();
	std::vector<colors> inline getCode()
	{
		return m_code;
	}
private:
	std::vector<colors> m_code;	//the code will be generated randomly by the computer.	
	
	int m_codeSize;
};