#include "Plains.hpp"


Plains::Plains()
{
}

Plains::Plains(int row, int col)
{
	spcTyp = 'P';
	name = "plains";
	creat = nullptr;
	this->row = row;
	this->col = col;

	//set level of difficulty
	setDifficulty();

	//generate resources
	genResources();

	//map pointers
	north = nullptr;
	south = nullptr;
	east = nullptr;
	west = nullptr;
}



string Plains::describe()
{
	return ""; //just for testing
}


Plains::~Plains()
{
}