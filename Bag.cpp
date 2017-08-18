/******************************************************************************
Class: Bag
Name: Russell Moon
Date: 8/12/2017
Description: This class models a bag carried by a Creature. It has an item
vector data member and functions for adding, removing and using items from
that vector. It also has a function for resizing the vector once an item has
been removed.
******************************************************************************/

#include "Bag.hpp"
#include <iostream>
#include "cs162_utilities.hpp"

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
bool Bag::addItm(shared_ptr<Item>item, bool dispMsg)
{
	//if item is nullptr, return false
	if(item == nullptr)
	{
		cout << endl;
		cout << "..." << endl << endl;
		pauseUntilEnter();
		return false;
	}

	//determine new weight
	int newWght = item->getWeight() + currWght;

	//determine if there's sufficient capacity with new item
	if (newWght <= capacity)
	{
		//add item to bag vector
		bagVect.push_back(item);
		//update current weight
		currWght = newWght;
		//if alter message should be displayed
		if (dispMsg)
		{
			cout << "Item added to bag: " << item->getName() << endl << endl;
			pauseUntilEnter();
		}

		return true;
	}

	//if capacity not large enough to accommodate new item
	return false;
	


}


//removes item from bag and returns item
shared_ptr<Item> Bag::rmvItm()
{
	//create bag item menu list
	vector<string> bagMenu;
	for (unsigned int i = 0; i < bagVect.size(); i++)
	{
		string rsc = bagVect[i]->getName();
		bagMenu.push_back(rsc);
	}


	//**********remove item from bag***************

	//if bag is empty, return nullptr
	if (bagVect.empty())
	{
		cout << "(bag is empty)" << endl << endl;
		return nullptr;
	}

	int menuChoice;
	
	
	//print out menu of resource choices and prompt user
	cout << "(choose an item from bag)" << endl;
	menuChoice = menuExit(bagMenu, false);
	cout << endl;


	//if user exits menu, return nullptr
	if (menuChoice == 0) 
	{
		return nullptr;
	}
			

	//point temp variable to item to add to bag
	shared_ptr<Item> itemToRmv = bagVect[menuChoice - 1];


	//remove the rsc from the bag vector and rewrite vector
	rmvVectItm(bagVect, menuChoice - 1);

	//reduce bag weight
	currWght = currWght - itemToRmv->getWeight();

	//output message upon completion
	cout << "Item removed from bag: " << itemToRmv->getName() << endl
		<<endl;


	return itemToRmv;
}



//returns item from bag if consumable and removes item from bag
shared_ptr<Item> Bag::consumeItem()
{
	//create bag item menu list
	vector<string> bagMenu;
	for (unsigned int i = 0; i < bagVect.size(); i++)
	{
		string rsc = bagVect[i]->getName();
		bagMenu.push_back(rsc);
	}


	//**********remove item from bag***************

	//if bag is empty, return nullptr
	if (bagVect.empty())
	{
		cout << "(bag is empty)" << endl << endl;
		return nullptr;
	}

	int menuChoice;


	//print out menu of resource choices and prompt user
	cout << "(choose an item from bag)" << endl;
	menuChoice = menuExit(bagMenu, false);
	cout << endl;


	//if user exits menu, return nullptr
	if (menuChoice == 0)
	{
		return nullptr;
	}


	//point temp variable to item to add to bag
	shared_ptr<Item> itemToCnsm = bagVect[menuChoice - 1];


	//if item not useable, return nullptr
	if(itemToCnsm->getSubclass() != "consumable")
	{
		cout << "That item can't be used." << endl << endl;
		return nullptr;
	}

	//remove the rsc from the bag vector and rewrite vector
	rmvVectItm(bagVect, menuChoice - 1);

	//reduce bag weight
	currWght = currWght - itemToCnsm->getWeight();

	//output message upon completion
	cout << "Item removed from bag: " << itemToCnsm->getName() << endl
		<< endl;


	return itemToCnsm;
}




//removes item by rewriting vector without removed item
//takes element number of item to remove from vector as a parameter
void Bag::rmvVectItm(vector<shared_ptr<Item>>& vect, int itmToRmv)
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


void Bag::dispContents()
{
	cout << "Bag Contents" << endl;
	cout << "************" << endl;

	for(unsigned i = 0; i<bagVect.size(); i++)
	{
		cout << "slot " << i+1<<") "<<bagVect[i]->getName() << endl;
	}

	if(bagVect.empty())
	{
		cout << "(empty)" << endl << endl;
	}
	else
	{
		cout << endl;
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

//returns bag vector (pass by reference)
vector<shared_ptr<Item>>& Bag::getBagVect()
{
	return bagVect;
}


Bag::~Bag()
{
}
