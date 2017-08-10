#include "Hero.hpp"
#include<iostream>

using std::cout;
using std::endl;


//default constructor with default coord of (3,3) and 25 str
Hero::Hero()
{
	this->row = 3;
	this->col = 3;
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(10);
	numAttDie = 2;
	numDefDie = 2;
	armor = 0;
	strength = 25;
	startingStrength = 25;
	name = "Hero";
}

//constructor that takes coord parameters
Hero::Hero(int row, int col, int strength, int numAttDie, int numDefDie,
	int bagCapacity) : Creature(bagCapacity) //: bag(bagCapacity)
{
	this->row = row;
	this->col = col;
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(10);
	this->numAttDie = numAttDie;
	this->numDefDie = numDefDie;
	armor = 0;
	this->strength = strength;
	startingStrength = strength;
	name = "Hero";
}


void Hero::refresh()
{
	strength = startingStrength;
}

//void Hero::chkInventory()
//{
//	//display bag capactiy and display contents
//	cout << "Bag capacity: " << bag.getCapacity() << endl;
//	cout << "Bag weight: " << bag.getCurrWght() << endl;
//	cout << endl;
//	bag.dispContents();
//}
//
////tries item to bag (returns true if completed and false if not)
//bool Hero::addToBag(shared_ptr<Item> item)
//{
//	bool addedToBag = bag.addItm(item);
//	return addedToBag;
//}

Hero::~Hero()
{
}
