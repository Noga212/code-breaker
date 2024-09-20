#pragma once
#include <random>
#include "Guess.h"

class Game
{
public:
	Game();
	int getResult();
private:
	std::vector<colors> m_code;	//the code will be generated randomly by the computer.	
	int m_result;		//counts the number of guesses until solving
	int m_codeSize;
};