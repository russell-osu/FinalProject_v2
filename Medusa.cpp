/******************************************************************************
Class: Medusa
Name: Russell Moon
Date: 8/2/2017
Description: Medusa is a subclass of Creature. It overrides the attack function
in order to implement the Glare attack (on an attack roll of 12, Medusa
activates Glare, which reduces opponent's strength to 0). 
******************************************************************************/

#include "Medusa.hpp"
#include "cs162_utilities.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;


Medusa::Medusa()
{
	attDie = std::make_shared<Die>(6);
	defDie = std::make_shared<Die>(6);
	numAttDie = 2;
	numDefDie = 1;
	armor = 3;
	strength = 8;
	name = "Medusa";
}

string Medusa::attack()
{
	//accumulator for attack rolls
	attRoll = 0;

	//roll die numAttDie number of times and accumulate points
	for (int i = 0; i<numAttDie; i++)
	{
		attRoll += attDie->roll();
	}


	//resolve Glare ability
	if(attRoll ==12)
	{
		//add special attack message to attack text
		string special = "**Medusa used Glare on opponent**";
		//generate attack text
		generateAttText(special);
		return "Glare";
	}
	else //if roll < 12
	{
		//generate attack text
		generateAttText();
		//convert attRoll to string so other functions can distinguish
		//between roll attacks and special attacks
		return to_string(attRoll);
	}
}

//resets creature to original state for new match
void Medusa::refresh()
{
	strength = 8;
}


Medusa::~Medusa()
{
}
