#include "Forest.hpp"


Forest::Forest()
{
}

Forest::Forest(int row, int col)
{
	spcTyp = 'F';
	name = "forest";
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



string Forest::describe()
{
	return ""; //just for testing
}


Forest::~Forest()
{
}
