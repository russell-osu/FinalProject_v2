/******************************************************************************
Class: Space
Name: Russell Moon
Date: 8/12/2017
Description: Abstract class Space models an individual cell on the game map.
Space can be instantiated as one of four subclasses: Village, Forest, Plain
or Hill. It has methods for generating the resource items contained by Space.
It also has methods for procedurally generating monsters that occupy the space
as well as the items that the monsters carry. Further it has methods for
setting the difficulty levels for different areas (the difficulty level 
increases as the player moves farther from the village).
******************************************************************************/

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
#include "AttPotion.hpp"
#include "Consumable.hpp"
#include "Resource.hpp"
#include "DefPotion.hpp"
#include "StrPotion.hpp"

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
	system(CLEAR_SCREEN);

	//bool for flagging whether rsc was gathered
	bool rscGathered = false;
	
	//add items to bag
	if(rscItmVect.empty())
	{
		cout << "There are no more resources to gather." << endl;
		pauseUntilEnter();
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
	cout << "Choose the resource you'd like to gather:"
		<< endl;
	int menuChoice = menuExit(rscMenu, false);
	cout << endl;


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
			cout << "Item not added. Bag capacity insufficient." << endl;
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
			cout << "Choose the resource you'd like to gather:"
				<< endl;
			menuChoice = menuExit(rscMenu, false);
			cout << endl;
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

void Space::addRscItm(shared_ptr<Item> item)
{
	rscItmVect.push_back(item);
}

void Space::addMiscItm(shared_ptr<Item> item)
{
	miscItmVect.push_back(item);
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

	//randomly generate items for creatures bag
	genCreatItems();
}


//randomly generate items for creature's bag
void Space::genCreatItems()
{
	//gen attack potion
	int attPotChnc = getRandIntInRange(1, 2);

	//generate attack potion if condition is met
	if (attPotChnc == 1)
	{
		shared_ptr<Item> potion = std::make_shared<AttPotion>();
		creat->addToBag(potion);
	}

	//gen defense potion
	int defPotChnc = getRandIntInRange(1, 2);

	//generate defense potion if condition is met
	if (defPotChnc == 1)
	{
		shared_ptr<Item> potion = std::make_shared<DefPotion>();
		creat->addToBag(potion);
	}


	//gen strength potion
	int strPotChnc = getRandIntInRange(1, 2);

	//generate strength potion if condition is met
	if (strPotChnc == 1)
	{
		shared_ptr<Item> potion = std::make_shared<StrPotion>();
		creat->addToBag(potion);
	}

}


//increment number of time space has been visited
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

//pass by reference
vector<shared_ptr<Item>>& Space::getRscItmVect()
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



