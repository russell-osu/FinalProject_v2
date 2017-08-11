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

//add items to village's rscItmVect to build shelter
bool Village::buildShelter()
{
	//count the resources types in the rsc vect to determine amt needed
	int stoneCnt = 0;
	int woodCnt = 0;
	int oreCnt = 0;






	return false;
}
