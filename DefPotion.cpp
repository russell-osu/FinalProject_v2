/******************************************************************************
Class:DefPotion
Name: Russell Moon
Date: 8/12/2017
Description: This class models a defense potion that raises a creatures
num of defense die when used. It has a use method which takes a pointer
to creature to alter its stats.
******************************************************************************/


#include "DefPotion.hpp"
#include <iostream>
#include "cs162_utilities.hpp"

using std::cout;
using std::endl;

DefPotion::DefPotion()
{
	name = "defense potion";
	weight = 1;
}

//uses defense potion
void DefPotion::use(shared_ptr<Creature> creat)
{
	//increase number of def die by 1
	int numDefDie = creat->getNumDefDie();
	creat->setNumDefDie(numDefDie + 1);

	cout << "Number of defense dice increased by 1." << endl << endl;
}


DefPotion::~DefPotion()
{
}
