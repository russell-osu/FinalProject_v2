#include "Bag.hpp"
#include <iostream>

using std::cout;
using std::endl;

Bag::Bag()
{
	this->capacity = 25;
	this->currWght = 0;
}

Bag::Bag(int capacity)
{
	this->capacity = capacity;
	this->currWght = 0;
}



//tries item to bag (returns true if completed and false if not)
bool Bag::addItm(shared_ptr<Item>item)
{
	//determine new weight
	int newWght = item->getWeight() + currWght;

	//determine if there's sufficient capacity with new item
	if (newWght <= capacity)
	{
		//add item to bag vector
		bagVect.push_back(item);
		//update current weight
		currWght = newWght;
		return true;
	}

	//if capacity not large enough to accommodate new item
	return false;
	


}


void Bag::dispContents()
{
	cout << "Bag Contents" << endl;
	cout << "************" << endl;

	for(unsigned i = 0; i<bagVect.size(); i++)
	{
		cout << "slot " << i+1<<") "<<bagVect[i]->getName() << endl;
	}
}

void Bag::setCapacity(int capacity)
{
	this->capacity = capacity;
}

int Bag::getCapacity()
{
	return capacity;
}

void Bag::setCurrWght(int currWght)
{
	this->currWght = currWght;
}

int Bag::getCurrWght()
{
	return currWght;
}

vector<shared_ptr<Item>> Bag::getBagVect()
{
	return bagVect;
}

Bag::~Bag()
{
}
