/******************************************************************************
Class: HarryPotter
Name: Russell Moon
Date: 8/2/2017
Description: HarryPotter is a subclass of Creature. It overrides the defend
function in order to implement the Hogwart's ability (if Harry Potter's 
strength is reduced to 0, then he is resurrected one time only with a new
strength of 20). HarryPotter also has an additional data member, lives, to
keep track of the number of live's remaining.
******************************************************************************/

#include "HarryPotter.hpp"
#include "cs162_utilities.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;


HarryPotter::HarryPotter()
{
	attDie = std::make_shared<Die>(6);
	defDie = std::make_shared<Die>(6);
	numAttDie = 2;
	numDefDie = 2;
	armor = 0;
	strength = 10;
	name = "Harry Potter";
	lives = 2;
}



int HarryPotter::defend(string attString)
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
	if (isInteger(attString,false)) 
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


	//resolve Hogwarts (resurrection)
	string special = "";
	if(lives > 1 && strength <= 0)
	{
		//add special ability activatation to defense text
		string special = "**Harry Potter activates Hogwarts and "
			"is resurrected**";
		strength = 20;
		lives--; //decrment number of lives
		
	}

	//generate defense text
	generateDefText(prelimStrength, special);

	return strength;
}

//resets creature to original state for new match
void HarryPotter::refresh()
{
	strength = 10;
	lives = 2;
}

void HarryPotter::setLives(int lives)
{
	this->lives = lives;
}

int HarryPotter::getLives()
{
	return lives;
}


HarryPotter::~HarryPotter()
{
}
