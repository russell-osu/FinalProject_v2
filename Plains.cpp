#include "Plains.hpp"


Plains::Plains()
{
}

Plains::Plains(int row, int col)
{
	spcTyp = 'P';
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

int Plains::gatherRsc()
{
	return 1; //just for testing
}


string Plains::describe()
{
	return ""; //just for testing
}


Plains::~Plains()
{
}
