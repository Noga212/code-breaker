#pragma once
#include <vector>
#include <string>

// a guess will contain 2 parts: the guess and the hint.
//the guess is a combination of colors (set to 4 in version 0.1) from the color database (represented by numbers).
//the hint will be a grup in the size o the combination (4 in version 0.1) from the database {black,white,blank}. represented {B,W,0}
//the GUI will translate this data.

enum colors { NA, red, yellow, blue, green, purple, orange };
enum hints { black, white };

class Guess 
{
	
public:
	Guess(std::vector<colors> theGuess);
	std::vector<colors>  getCombination();
	void calculateHint(std::vector<colors> code);
	
	unsigned int inline getBlack()
	{
		return m_hintBlack;
	}

	unsigned int inline getWhite()
	{
		return m_hintWhite;
	}


private:
	const std::vector<colors> m_combination;
	unsigned int m_hintBlack;			//note: the hint is all blacks first and then all whites. hint size <= combination size
	unsigned int m_hintWhite;
};