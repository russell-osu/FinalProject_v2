#include "Village.hpp"


Village::Village()
{
}

Village::Village(int row, int col)
{
	spcTyp = 'V';
	creat = nullptr;
	this->row = row;
	this->col = col;
	diffLvl = 0;

	//map pointers
	north = nullptr;
	south = nullptr;
	east = nullptr;
	west = nullptr;
}

int Village::gatherRsc()
{
	return 1; //just for testing
}


string Village::describe()
{
	return ""; //just for testing
}

Village::~Village()
{
}
