#include "Forest.hpp"


Forest::Forest()
{
}

Forest::Forest(int row, int col)
{
	spcTyp = 'F';
	creat = nullptr;
	this->row = row;
	this->col = col;

	//set level of difficulty
	setDifficulty();

	//map pointers
	north = nullptr;
	south = nullptr;
	east = nullptr;
	west = nullptr;
}

int Forest::gatherRsc()
{
	return 1; //just for testing
}


string Forest::describe()
{
	return ""; //just for testing
}


Forest::~Forest()
{
}
