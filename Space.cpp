#include "Space.hpp"
#include "defConst.hpp"
#include "cs162_utilities.hpp"
#include "Stone.hpp"
#include "Wood.hpp"
#include "Ore.hpp"


Space::Space()
{
}


//generates a random number of natural resources, based on diff lvl of space
//and then adds those resources to the rsc items vector
void Space::genResources()
{
	
	//determine num of resources, based on difficulty level
	int numRsc = diffLvl * getRandIntInRange(1, 3);

	if (this->getSpcTyp() == 'P') //if plains, gen stone
	{
		shared_ptr<Item> tmpItm = std::make_shared<Stone>();
		rscItmVect.push_back(tmpItm);
	}
	if (this->getSpcTyp() == 'F') //if forest, gen wood
	{
		shared_ptr<Item> tmpItm = std::make_shared<Wood>();
		rscItmVect.push_back(tmpItm);
	}
	if (this->getSpcTyp() == 'H') //if hills, gen ore
	{
		shared_ptr<Item> tmpItm = std::make_shared<Ore>();
		rscItmVect.push_back(tmpItm);
	}

}

int Space::gatherRsc()
{
	return 0; //just for testing
}

void Space::setRow(int row)
{ 
	this->row = row;
}

int Space::getRow()
{
	return row;
}

void Space::setCol(int col)
{
	this->col = col;
}

int Space::getCol()
{
	return col;
}

void Space::setCreat(Creature* creat)
{
	this->creat = creat;
}

Creature* Space::getCreat()
{
	return creat;
}


void Space::setSpcTyp(char spcTyp)
{
	this->spcTyp = spcTyp;
}

char Space::getSpcTyp()
{
	return spcTyp;
}

void Space::setDiffLvl(int diffLvl)
{
	this->diffLvl = diffLvl;
}

int Space::getDiffLvl()
{
	return diffLvl;
}

void Space::setNorth(Space* north)
{
	this->north = north;
}

Space* Space::getNorth()
{
	return north;
}

void Space::setSouth(Space* south)
{
	this->south = south;
}

Space* Space::getSouth()
{
	return south;
}

void Space::setEast(Space* east)
{
	this->east = east;
}

Space* Space::getEast()
{
	return east;
}

void Space::setWest(Space* west)
{
	this->west = west;
}

Space* Space::getWest()
{
	return west;
}


Space::~Space()
{
}


//difficulty level of space is equal to the greater of the number of rows
//or the num of cols removed from the starting village
void Space::setDifficulty()
{
	int rowDepth = abs(VILLAGE_ROW - row);
	int colDepth = abs(VILLAGE_COL - col);

	if (rowDepth>colDepth)
	{
		diffLvl = rowDepth;
	}
	else if(colDepth>rowDepth)
	{
		diffLvl = colDepth;
	}
	else
	{
		diffLvl = rowDepth;
	}
}
