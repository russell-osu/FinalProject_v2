#include "Hills.hpp"



Hills::Hills()
{
}

Hills::Hills(int row, int col)
{
	spcTyp = 'H';
	name = "hills";
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

int Hills::gatherRsc()
{
	return 1; //just for testing
}


string Hills::describe()
{
	return ""; //just for testing
}


Hills::~Hills()
{
}
