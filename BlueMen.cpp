/******************************************************************************
Class: BlueMen
Name: Russell Moon
Date: 8/2/2017
Description: Blue Men is a subclass of Creature. It overrides the defend method
in order to implement the Mob weakness (for each 4 points of damage, Blue Men
lose 1 defense die).


******************************************************************************/

#include "BlueMen.hpp"
#include "cs162_utilities.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;


BlueMen::BlueMen()
{
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(6);
	numAttDie = 2;
	numDefDie = 3;
	armor = 3;
	strength = 12;
	name = "Blue Men";
}

int BlueMen::defend(string attString)
{

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
	int attInt = 0; //attString converted to int

	//if attack was a regular attack (roll of dice)
	if (isInteger(attString, false)) 
	{
		attInt = stoi(attString);

		//reduce attack by armor and defense roll
		attInt = attInt - (armor + defRoll); 

		//only reduce strength if damage > 0									 
		if (attInt > 0)
		{
			strength = strength - attInt;
		}
	}
	else if (attString == "Glare")
	{
		strength = 0;
	}


	//resolve Mob (defense die multiplier reduction)
	string special = "";
	int newDefDieMult = numDefDie;
	if (strength <= 8 && strength >= 5 && numDefDie > 2)
	{
		//output activation of special weakness
		special = "**Mob activates and Blue Men now have "
			"2d6 for defense**";
		newDefDieMult = 2;
	}
	else if (strength <= 4 && numDefDie > 1)
	{
		//output activation of special weakness
		special = "**Mob activates and Blue Men now have "
			"1d6 for defense**";
		newDefDieMult = 1;
	}

	//generate defense text
	generateDefText(prelimStrength, special);

	//set defense die multiplier (if changed by Mob)
	numDefDie = newDefDieMult;

	//return strength
	return strength;

}

//resets creature to original state for new match
void BlueMen::refresh()
{
	strength = 12;
	numDefDie = 3;
}


BlueMen::~BlueMen()
{
}
