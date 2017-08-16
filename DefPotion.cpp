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
