#include "Village.hpp"
#include <iostream>
#include "defConst.hpp"
#include "cs162_utilities.hpp"

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
	//bool itemAdded = false;

	//if hero's bag has no resources, return false
	bool noRsc = true;
	Bag* heroBag = hero->getBag();
	vector<shared_ptr<Item>>& heroBagVect = heroBag->getBagVect();
	for(unsigned i = 0; i<heroBagVect.size(); i++)
	{
		if(heroBagVect[i]->getSubclass()=="resource")
		{
			noRsc = false;
		}

	}
	if (noRsc)
	{
		cout << "You have no resources to add." << endl << endl;
		return false;
	}

	//display current shelter resources
	dispSheltRsc();

	//promt user to remove item from bag
	cout << "Add to shelter resource supply:" << endl;
	

	//list items and prompt user to rmv item from bag
	shared_ptr<Item> buildItm;
	buildItm = hero->rmvFromBag();

	//if item added is not a resource, alert user, return item
	//to bag and return false
	if(buildItm->getSubclass() != "resource")
	{
		cout << "Item chosen is not a resource." << endl << endl;
		heroBag->addItm(buildItm);
		return false;
	}


	cout << endl;

	//loop through hero's bag vector to remove rsc items
	while (buildItm != nullptr)
	{
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

		//check win conditions and return true if won
		if (stoneCnt >= stoneWin && woodCnt >= woodWin && oreCnt >= oreWin)
		{
			cout << "YOU HAVE COLLECTED ALL THE RESOURCES NEEDED!!" << endl;
			cout << "(press <enter> to continue)" << endl;
			pauseUntilEnter();
			//enough resources collected to build shelter
			return true;
		}


		//if hero's bag has no more rsc, return false
		noRsc = true;
		for (unsigned i = 0; i<heroBagVect.size(); i++)
		{
			if (heroBagVect[i]->getSubclass() == "resource")
			{
				noRsc = false;
			}

		}
		if (noRsc)
		{
			cout << "You have no resources to add." << endl << endl;
			pauseUntilEnter();
			return false;
		}

		//prompt user to remove another item from bag
		cout << "Add to shelter resource supply:" << endl;
		buildItm = hero->rmvFromBag();

		//if item added is not a resource, alert user, return item
		//to bag and return false
		if (buildItm->getSubclass() != "resource" && buildItm != nullptr)
		{
			cout << "Item chosen is not a resource." << endl << endl;
			heroBag->addItm(buildItm);
			return false;
		}
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

