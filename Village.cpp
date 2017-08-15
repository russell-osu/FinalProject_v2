#include "Village.hpp"
#include <iostream>
#include "defConst.hpp"

using std::cout;
using std::endl;



Village::Village()
{
}

Village::Village(int row, int col, int stone, int wood, int ore)
{
	spcTyp = 'V';
	creat = nullptr;
	this->row = row;
	this->col = col;
	diffLvl = 0;
	stoneCnt = 0;
	woodCnt = 0;
	oreCnt = 0;

	//resources needed to build shelter
	this->stoneWin = stone;
	this->woodWin = wood;
	this->oreWin = ore;

	//map pointers
	north = nullptr;
	south = nullptr;
	east = nullptr;
	west = nullptr;
}



string Village::describe()
{
	return ""; //just for testing
}

Village::~Village()
{
}



//add items to village's rscItmVect to build shelter
//returns true if shelter is completed
bool Village::buildShelter(shared_ptr<Creature>hero)
{
	bool itemAdded = false;

	//if hero's bag is empty, return false
	if(hero->bagIsEmpty())
	{
		cout << "You have no resources to add." << endl << endl;
		return false;
	}

	//display current shelter resources
	dispSheltRsc();

	//promt user to remove item from bag
	cout << "Add to shelter resource supply:" << endl;
	shared_ptr<Item> buildItm = hero->rmvFromBag();
	cout << endl;

	while (buildItm != nullptr)
	{
		itemAdded = true;

		//add item to shelter rsc vector
		rscItmVect.push_back(buildItm);

		//increment rsc count
		char rscTyp = buildItm->getType();
		switch (rscTyp)
		{
		case 's': stoneCnt++;
			break;
		case 'w': woodCnt++;
			break;
		case 'o': oreCnt++;
			break;
		}

		//clear screen and display shelter resources
		system(CLEAR_SCREEN);
		dispSheltRsc();

		//prompt user to remove another item from bag
		cout << "Add to shelter resource supply:" << endl;
		buildItm = hero->rmvFromBag();

	}


	//check win conditions
	if(stoneCnt >= stoneWin && woodCnt >= woodWin && oreCnt >= oreWin)
	{	
		cout << "YOU HAVE COLLECTED ALL THE RESOURCES NEEDED!!" << endl;
		cout << "(press <enter> to continue)" << endl;
		std::cin.ignore(INT_MAX, '\n');
		//enough resources collected to build shelter
		return true;
	}

	//not enough resources collected, yet
	return false;

	}




//count and display current resources provided to shelter
void Village::dispSheltRsc()
{
	cout << "Current Shelter Resources" << endl;
	cout << "*************************" << endl;
	cout << "Stone: " << stoneCnt << " of " <<
		stoneWin << " added to shelter" << endl;

	cout << "Wood: " << woodCnt << " of " <<
		woodWin << " added to shelter" << endl;

	cout << "Ore: " << oreCnt << " of " <<
		oreWin << " added to shelter" << endl << endl;

}

void Village::setStoneCnt(int stone)
{
	stoneCnt = stone;
}

int Village::getStoneCnt()
{
	return stoneCnt;
}

void Village::setWoodCnt(int wood)
{
	woodCnt = wood;
}

int Village::getWoodCnt()
{
	return woodCnt;
}

void Village::setOreCnt(int ore)
{
	oreCnt = ore;
}

int Village::getOreCnt()
{
	return oreCnt;
}


int Village::getStoneWin()
{
	return stoneWin;
}

int Village::getWoodWin()
{
	return woodWin;
}

int Village::getOreWin()
{
	return oreWin;
}

