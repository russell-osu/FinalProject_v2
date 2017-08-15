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

void AttPotion::use(shared_ptr<Creature> creat)
{
	//increase number of att die by 1
	int numAttDie = creat->getNumAttDie();
	creat->setNumAttDie(numAttDie + 1);

	cout << "Number of attack dice increased by 1." << endl;
	pauseUntilEnter();

}


AttPotion::~AttPotion()
{
}
