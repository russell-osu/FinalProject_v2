/******************************************************************************
Class: Vampire
Name: Russell Moon
Date: 8/2/2017
Description: Vampire is a subclass of Creature. It overrides the defend method
in order to implement the Charm defense (50% of the time, Vampire prevent 
opponent from attacking).
******************************************************************************/

#include "Vampire.hpp"
#include "cs162_utilities.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;

//default constructor
Vampire::Vampire()
{
	attDie = std::make_shared<Die>(12);
	defDie = std::make_shared<Die>(6);
	numAttDie = 1;
	numDefDie = 1;
	armor = 1;
	strength = 18;
	name = "Vampire";
}

int Vampire::defend(string attString)
{

	//check to see if Charm activates; if it does, strength remains the same
	//and defense roll is 0 (since vampire didn't have to roll to defend)
	//special attacks don't have an effect since strength is returned 
	//immediately)
	if (getRandIntInRange(1, 2) == 1)
	{
		defRoll = 0;
		//add special defense message to defense text
		string special = "**Vampire charmed opponent**";
		//generate standard defense text
		generateDefText(strength, special);

		return strength;
	}

	//strength at the beginning of this round
	//used for round info output
	int prelimStrength = strength;


	//accumulator for defense rolls
	defRoll = 0;

	//roll die numDefDie number of times and accumulate points
	for (int i = 0; i<numDefDie; i++)
	{
		defRoll += defDie->roll();
	}

	//determine if attString is integer or special attack and resolve attack
	int attInt; //attString converted to int

	//if attack was a regular attack (roll of dice)
	if (isInteger(attString, false)) 
	{
		attInt = stoi(attString);
		attInt -= armor + defRoll; //reduce attack by armor and defense roll

		//only reduce strength if damage > 0
		if (attInt > 0)
		{
			strength -= attInt;
		}
	}
	else if (attString == "Glare")
	{
		strength = 0;
	}

	//generate defense text
	generateDefText(prelimStrength);


	//return strength
	return strength;
}


Vampire::~Vampire()
{
}

//resets creature to original state for new match
void Vampire::refresh()
{
	strength = 18;
}
