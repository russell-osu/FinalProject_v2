
/******************************************************************************
Class:Att Potion
Name: Russell Moon
Date: 8/12/2017
Description: This class models an attack potion that raises a creatures
num of attack die when used. It has a use method which takes a pointer
to creature to alter its stats.
******************************************************************************/

#include "AttPotion.hpp"
#include <iostream>
#include "cs162_utilities.hpp"

using std::cout;
using std::endl;

AttPotion::AttPotion()
{
	name = "attack potion";
	weight = 1;
}

//uses attack potion
void AttPotion::use(shared_ptr<Creature> creat)
{
	//increase number of att die by 1
	int numAttDie = creat->getNumAttDie();
	creat->setNumAttDie(numAttDie + 1);

	cout << "Number of attack dice increased by 1." << endl << endl;
	
}


AttPotion::~AttPotion()
{
}
