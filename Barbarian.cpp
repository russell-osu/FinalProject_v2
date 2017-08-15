/******************************************************************************
Class: Barbarian
Name: Russell Moon
Date: 8/2/2017
Description: Barbarian is a subclass of Creature. Barbarian has no special
attack or defense abilities.
******************************************************************************/

#include "Barbarian.hpp"


//default constructor for Barbarian
Barbarian::Barbarian() 
{
	attDie = std::make_shared<Die>(6);
	defDie = std::make_shared<Die>(6);
	numAttDie = 2;
	numDefDie = 2;
	armor = 0;
	strength = 12;
	name = "Barbarian";
}

//resets creature to original state for new match
void Barbarian::refresh()
{
	strength = 12;
}


Barbarian::~Barbarian()
{
}
