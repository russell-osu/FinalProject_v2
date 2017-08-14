/******************************************************************************
Class: Creature
Name: Russell Moon
Date: 8/2/2017
Description: This is the abstract base class for a group of battle creatures,
each of which have different stats and attack and defense abilities. Creature
has data members for an attack die and a defense die (which may have a 
different number of sides). It has data members for the number of attack die
and number of defense die. It has data members for armor, strength (hit 
points), and name (the type of inheriting subclass). It also has data members
for the attack text and defense text which is generated by each creature at
the end of the round. It's main methods are attack, which generates an attack
roll (returning a string to handle special ability attacks). The other main
method is defend, which returns the resulting strength of the creature after
combat and takes a string (generated by another creatures attack function).
It also has a pure virtual function, refresh, that resets creatures to their
original state for a new match (for multi-match trials).
******************************************************************************/

#include "Creature.hpp"
#include "cs162_utilities.hpp"

#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;



//generates attack roll; returns a string number 
//representing the attack roll for standard attacks
//and a non-numeric descriptor for special ability attacks)
string Creature::attack()
{
	//accumulator for attack rolls
	attRoll = 0;

	//roll die numAttDie number of times and accumulate points
	for(int i=0; i<numAttDie; i++)
	{
		attRoll += attDie->roll();
	}

	//create attack text
	generateAttText();
				
	//convert attRoll to string so other functions can distinguish
	//between roll attacks and special attacks
	return to_string(attRoll);
}



//generates defense roll, applies combat modifiers 
//and returns resulting strength; takes a string as a parameter to 
//handle special attacks
int Creature::defend(string attString)
{
	//strength at the beginning of this round
	//used for round info output
	int prelimStrength = strength;
	
	//accumulator for defense rolls
	defRoll = 0;

	//roll die numDefDie number of times and accumulate points
	for(int i=0; i<numDefDie; i++)
	{
		defRoll += defDie->roll();
	}

	//determine if attString is integer or special attack and resolve attack
	int attInt = 0; //used if attString is converted to int

	//if attack was a regular attack (roll of dice)
	if(isInteger(attString, false)) 
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
	else if(attString == "Glare")
	{
		strength = 0;
	}


	//create defense text
	generateDefText(prelimStrength);

	//return strength
	return strength;

}


//generate attack text
void Creature::generateAttText(string special)
{
	//generate attack text
	attText.str(""); //clear stream;
	attText << "Attacker: " << name << " | Att Dice: " <<
		numAttDie << "d" << getAttDieSides() << " | Att Roll: "
		<< attRoll;
	if (special != "")
	{
		attText << endl << special;
	}
}

//generate defense text
void Creature::generateDefText(int prelimStrength, string special)
{
	//generate defense text
	defText.str(""); //clear previous round's text
	defText << "Defender: " << name << " | Def Dice: " <<
		numDefDie << "d" << getDefDieSides() << " | Def Roll: "
		<< defRoll << " | Armor: " << armor << endl;
	if (special != "")
	{
		defText << special << endl;
	}

	defText << endl << "Attack Damage: " << prelimStrength - strength << endl;
	defText << "Defender's strength before attack: " << prelimStrength << endl;
	defText << "Defender's strength after attack: " << strength;
}


void Creature::chkInventory()
{
	//display bag capactiy and display contents
	cout << "Bag capacity: " << bag.getCapacity() << endl;
	cout << "Bag weight: " << bag.getCurrWght() << endl;
	cout << endl;
	bag.dispContents();

	//present option to rmv item from bag if bag is not empty
	if (!bag.getBagVect().empty())
	{
		string menuItems[] = { "yes", "no" };
		cout << "Remove an item from the bag?" << endl;
		int menuChoice = menu(menuItems, 2, false);
		cout << endl;
		if (menuChoice == 1)
		{
			this->rmvFromBag();
		}
	}
}

//tries item to bag (returns true if completed and false if not)
bool Creature::addToBag(shared_ptr<Item> item)
{
	bool addedToBag = bag.addItm(item);
	return addedToBag;
}


//removes item from bag and returns item
//returns nullptr if nothing removed
shared_ptr<Item> Creature::rmvFromBag()
{
	return bag.rmvItm();
}



void Creature::setNumAttDie(int numAttDie)
{
	this->numAttDie = numAttDie;
}


int Creature::getNumAttDie()
{
	return numAttDie;
}


void Creature::setNumDefDie(int numDefDie)
{
	this->numDefDie = numDefDie;
}


int Creature::getNumDefDie()
{
	return numDefDie;
}


void Creature::setArmor(int armor)
{
	this->armor = armor;
}

int Creature::getArmor()
{
	return armor;
}


void Creature::setStrength(int strength)
{
	this->strength = strength;
}

int Creature::getStrength()
{
	return strength;
}


void Creature::setName(string name)
{
	this->name = name;
}


string Creature::getName()
{ 
	return name;
}


void Creature::setDefRoll(int defRoll)
{
	this->defRoll = defRoll;
}

int Creature::getDefRoll()
{
	return defRoll;
}


void Creature::setAttRoll(int attRoll)
{
	this->attRoll = attRoll;
}


int Creature::getAttRoll()
{
	return attRoll;
}


int Creature::getAttDieSides()
{
	return attDie->getNumSides();
}


int Creature::getDefDieSides()
{
	return defDie->getNumSides();
}


//returns true if bag is empty
bool Creature::bagIsEmpty()
{
	if(bag.getBagVect().empty())
	{
		return true;
	}

	return false;
}


string Creature::getAttText()
{
	string strAttText = attText.str();
	return strAttText;
}


string Creature::getDefText()
{
	string strDefText = defText.str();
	return strDefText;
}

void Creature::setRow(int row)
{
	this->row = row;
}

int Creature::getRow()
{
	return row;
}

void Creature::setCol(int col)
{
	this->col = col;
}

int Creature::getCol()
{
	return col;
}


Creature::Creature()
{
	
}

//initializes bag with a specified capacity
Creature::Creature(int bagCapacity) : bag(bagCapacity)
{
}


Creature::~Creature()
{
}
