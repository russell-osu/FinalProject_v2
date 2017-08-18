/******************************************************************************
Class: Forest
Name: Russell Moon
Date: 8/12/2017
Description: This is a subclass of Space that models a forest. It contains
the wood resource.
******************************************************************************/


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


//function stub -- may be used in later versions
string Forest::describe()
{
	return ""; //just for testing
}


Forest::~Forest()
{
}
