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
