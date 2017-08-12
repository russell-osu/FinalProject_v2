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
	this->stoneNeed = stone;
	this->woodNeed = wood;
	this->oreNeed = ore;

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

	//display current shelter resources
	dispSheltRsc();

	//promt user to remove item from bag
	cout << "Add to shelter resource supply:" << endl;
	shared_ptr<Item> buildItm = hero->rmvFromBag();

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

		//prompt user to remove another item from bag
		cout << "Add to shelter resource supply:" << endl;
		buildItm = hero->rmvFromBag();

	}

	if (itemAdded)
	{
		dispSheltRsc();
	}

	//check win conditions
	if(stoneCnt >= 10 && woodCnt >= 10 && oreCnt >= 10)
	{	
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
	cout << "Stone: " << stoneCnt << " (" <<
		stoneNeed - stoneCnt << " needed)" << endl;
	cout << "Wood: " << woodCnt << " (" <<
		woodNeed - woodCnt << " needed)" << endl;
	cout << "Ore: " << oreCnt << " (" <<
		oreNeed - oreCnt << " needed)" << endl << endl;

}


////count the resources types in the rsc vect to determine amt needed
//void Village::cntSheltRsc()
//{
//	for (unsigned i = 0; i < rscItmVect.size(); i++)
//	{
//		char rscTyp = rscItmVect[0]->getType();
//
//		switch (rscTyp)
//		{
//		case 's': stoneCnt++;
//			break;
//		case 'w': woodCnt++;
//			break;
//		case 'o': oreCnt++;
//			break;
//		}
//	}
//}




