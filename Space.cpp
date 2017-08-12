#include "Space.hpp"
#include "defConst.hpp"
#include "cs162_utilities.hpp"
#include "Stone.hpp"
#include "Wood.hpp"
#include "Ore.hpp"
#include <iostream>
#include "Hero.hpp"
#include "Vampire.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"
#include "Barbarian.hpp"

using std::cout;
using std::endl;

Space::Space()
{
	creat = nullptr;
	numVisits = 0;
}


//generates a random number of natural resources, based on diff lvl of space
//and then adds those resources to the rsc items vector
void Space::genResources()
{
	
	//determine num of resources, based on difficulty level
	int numRsc = diffLvl * getRandIntInRange(1, 3);

	if (this->getSpcTyp() == 'P') //if plains, gen stone
	{
		for (int i = 0; i < numRsc; i++)
		{
			shared_ptr<Item> tmpItm = std::make_shared<Stone>();
			rscItmVect.push_back(tmpItm);
		}
	}
	if (this->getSpcTyp() == 'F') //if forest, gen wood
	{
		for (int i = 0; i < numRsc; i++)
		{
			shared_ptr<Item> tmpItm = std::make_shared<Wood>();
			rscItmVect.push_back(tmpItm);
		}
	}
	if (this->getSpcTyp() == 'H') //if hills, gen ore
	{
		for (int i = 0; i < numRsc; i++)
		{
			shared_ptr<Item> tmpItm = std::make_shared<Ore>();
			rscItmVect.push_back(tmpItm);
		}
	}

}

void Space::dispRscItmVect()
{
	for(unsigned int i = 0; i < rscItmVect.size(); i++)
	{
		cout << rscItmVect[i]->getName() << endl;
	}
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
	else if (colDepth>rowDepth)
	{
		diffLvl = colDepth;
	}
	else
	{
		diffLvl = rowDepth;
	}
}

//gather rsc from rscItmVect, returns true if rsc gathered
bool Space::gatherRsc(shared_ptr<Creature>hero)
{
	//bool for flagging whether rsc was gathered
	bool rscGathered = false;
	
	//add items to bag
	if(rscItmVect.empty())
	{
		cout << "There are no more resources to gather." << endl;
		return rscGathered;
	}

	//create a string vector of resource items for later use in menu
	vector<string> rscMenu;
	for (unsigned int i = 0; i < rscItmVect.size(); i++)
	{
		string rsc = rscItmVect[i]->getName();
		rscMenu.push_back(rsc);
	}

	//print out menu of resource choices and prompt user
	cout << "Choose the resource you'd like to add:"
		<< endl;
	int menuChoice = menuExit(rscMenu, false);


	//gathering loop (allows user to gather multiple rsc)
	while (menuChoice != 0)
	{

		//point temp variable to item to add to bag
		shared_ptr<Item> itemToGet = rscItmVect[menuChoice - 1];

		//add item to hero's bag
		bool added = hero->addToBag(itemToGet);

		if (added) //bag had capacity
		{
			cout << "Item added to bag: " << itemToGet->getName() 
			<< endl;
			//remove the resource from the rscItmVect
			rmvVectItm(rscItmVect, menuChoice - 1);
			rscGathered = true;
		}
		else //bag lacked capacity
		{
			cout << "Your bag is full. Can't add resource." << endl;
		}

	
		if (rscItmVect.size() > 0) //if items remain to gather
		{
			//recreate string vector of resource items for later use in menu
			vector<string> rscMenu;
			for (unsigned int i = 0; i < rscItmVect.size(); i++)
			{
				string rsc = rscItmVect[i]->getName();
				rscMenu.push_back(rsc);
			}

			//print out menu of resource choices and prompt user
			cout << "Choose the resource you'd like to add:"
				<< endl;
			menuChoice = menuExit(rscMenu, false);
		}
		else //menu choice = 0, end loop
		{
			menuChoice = 0;
		}
	} 
	
	return rscGathered;
}




//removes item by rewriting vector without removed item
//takes element number of item to remove from vector as a parameter
void Space::rmvVectItm(vector<shared_ptr<Item>>& vect, int itmToRmv)
{
	//set element to nullptr
	vect[itmToRmv] = nullptr;
	


	//rewrite rsc vector to remove null element and rewrite rsc menu

	//create tmp rsc vector to hold remaining items
	vector<shared_ptr<Item>> tmpRscVect;
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		if (vect[i] != nullptr)
		{
			tmpRscVect.push_back(vect[i]);
		}
	}

	//clear resource vector and add tmp vector itms to cleared rsc vector
	//setting a cleared vector's size to 0: 
	//https://stackoverflow.com/questions/6882799/
	//does-clearing-a-vector-affect-its-capacity
	vect.clear();
	vector<shared_ptr<Item>>(vect).swap(vect);
	for (unsigned int i = 0; i < tmpRscVect.size(); i++)
	{
		vect.push_back(tmpRscVect[i]);
	}
}





//randomly generate creature and set its stats based on space diff lvl
void Space::genCreature()
{
	int creatTyp = getRandIntInRange(1, 5);

	switch(creatTyp)
	{
	case 0: //No creature
		creat = nullptr;
		break;
	case 1: //Vampire
		creat = std::make_shared<Vampire>();
		break;
	case 2: //BlueMen
		creat = std::make_shared<BlueMen>();
		break;
	case 3: //Harry Potter
		creat = std::make_shared<HarryPotter>();
		break;
	case 4: //Barbarian
		creat = std::make_shared<Barbarian>();
		break;
	case 5: //Medusa
		creat = std::make_shared<Medusa>();
		break;
	}

	//set strength
	int strength = creat->getStrength();
	creat->setStrength(strength*diffLvl);
	//set num att Die
	int numAttDie = creat->getNumAttDie();
	creat->setNumAttDie(numAttDie*diffLvl);
	//set num def Die
	int numDefDie = creat->getNumDefDie();
	creat->setNumDefDie(numDefDie*diffLvl);
}

void Space::incrementNumVisits()
{
	numVisits++;
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

void Space::setCreat(shared_ptr<Creature> creat)
{
	this->creat = creat;
}

shared_ptr<Creature> Space::getCreat()
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

void Space::setName(string name)
{
	this->name = name;
}

string Space::getName()
{
	return name;
}


void Space::setNumVisits(int numVisits)
{
	this->numVisits = numVisits;
}

int Space::getNumVisits()
{
	return numVisits;
}

vector<shared_ptr<Item>> Space::getRscItmVect()
{
	return rscItmVect;
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



