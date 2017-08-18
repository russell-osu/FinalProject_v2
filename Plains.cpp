/******************************************************************************
Class: Plains
Name: Russell Moon
Date: 8/12/2017
Description: Plains is a subclass of Space. It provides the stone resource.
******************************************************************************/

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


//stub for future implementation
string Plains::describe()
{
	return ""; //just for testing
}


Plains::~Plains()
{
}
