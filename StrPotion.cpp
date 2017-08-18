/******************************************************************************
Class: StrPotion
Name: Russell Moon
Date: 8/12/2017
Description: This class models a strength potion that raises a creatures
strength when used. It has a use method which takes a pointer
to creature to alter its stats.
******************************************************************************/


#include "StrPotion.hpp"
#include <iostream>
#include "cs162_utilities.hpp"

using std::cout;
using std::endl;


StrPotion::StrPotion()
{
	name = "strength potion";
	weight = 1;
}

//use of potion increases strength
void StrPotion::use(shared_ptr<Creature> creat)
{
	//increase creature strength by 150
	int strength = creat->getStrength();
	creat->setStrength(strength + 150);

	cout << "Strength increased by 150." << endl << endl;
}


StrPotion::~StrPotion()
{
}
