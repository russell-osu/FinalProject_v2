/******************************************************************************
Class: Combat
Name: Russell Moon
Date: 8/2/2017
Description: Class combat manages the combat between Creature class sub-types.
It has 2 pointers to Creature, one for Creature 1 and another for Creature 2.
It has method engage(), which manages the main logic for the fight. It has 
method chooseCreatures(), which prompts the user to select the type of each
creature. It also has method runTrials (not in the specs), which pits two 
creatures against each other for up to 1000 matches and then displays how many
times each creature won.
******************************************************************************/

#include "Combat.hpp"
#include "cs162_utilities.hpp"
#include <iostream>
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "BlueMen.hpp"
#include "Medusa.hpp"
#include "HarryPotter.hpp"
#include "Hero.hpp"

using std::cout;
using std::endl;
using std::stoi;
using std::make_shared;



//handles main logic for a round of combat
//returns winning combatant
shared_ptr<Creature> Combat::engage(shared_ptr<Creature> hero, 
	shared_ptr<Creature> mob)
{
	this->creat1 = hero;
	this->creat2 = mob;
	
	bool fightFinished = false;
	int round = 1; //initialize round counter


	//for differentiating b/w creatues of the same type
	string attCreatID = "";
	string defCreatID = "";

	//randomly determine first attacker
	shared_ptr<Creature> attacker;
	shared_ptr<Creature> defender;

	if(getRandIntInRange(1,2) == 1)
	{
		attacker = creat1;
		defender = creat2;
	}
	else
	{
		attacker = creat2;
		defender = creat1;
	}


	//loop until fight is finished
	do
	{	
		//display round info
		cout << "ROUND: " << round << endl;
		cout << "**********" << endl;

		//attString is value of attack roll or special ability
		string attString = attacker->attack();
		//returns defender's resulting strength after defense
		int defStrength = defender->defend(attString);

		//output attacker's info
		cout << attacker->getAttText() << endl << endl;
		
		//output defender's info
		cout << defender->getDefText() << endl << endl;


		//determine if fight is finished by checking defender's strength
		if(defStrength <= 0)
		{
			//output victory message
			cout << attacker->getName() << " wins!!!" << endl << endl;
			fightFinished = true;
		}

		else //get ready for next round
		{
			//swap attacker and defender
			shared_ptr<Creature> temp = attacker;
			attacker = defender;
			defender = temp;
		}

		round++; //increment round

	} while (!fightFinished);

	//returns winner of fight
	return attacker;
}



//allows user to choose the two creatues that will fight
void Combat::chooseCreatures()
{
	string creatMenu[] = { "Vampire",
							"Barbarian",
							"Blue Men",
							"Medusa",
							"Harry Potter",
							"Hero"};

	//prompt user to choose first creature
	cout << "Choose Creature 1: " << endl;
	int creat1Choice = menu(creatMenu, 6, false);
	cout << endl;

	//initialize creat1
	switch(creat1Choice)
	{
		case 1: creat1 = make_shared<Vampire>();
			break;
		case 2: creat1 = make_shared<Barbarian>();
			break;
		case 3: creat1 = make_shared<BlueMen>();
			break;
		case 4: creat1 = make_shared<Medusa>();
			break;
		case 5: creat1 = make_shared<HarryPotter>();
			break;
		case 6: creat1 = make_shared<Hero>();
			break;
	}


	//prompt user to choose second creature
	cout << "Choose Creature 2: " << endl;
	int creat2Choice = menu(creatMenu, 6, false);
	cout << endl;

	//initialize creat2
	switch (creat2Choice)
	{
		case 1: creat2 = make_shared<Vampire>();
			break;
		case 2: creat2 = make_shared<Barbarian>();
			break;
		case 3: creat2 = make_shared<BlueMen>();
			break;
		case 4: creat2 = make_shared<Medusa>();
			break;
		case 5: creat2 = make_shared<HarryPotter>();
			break;
		case 6: creat2 = make_shared<Hero>();
			break;
	}
}



//allows user to set creature strength to custom value
void Combat::changeStrength()
{
	//prompt user to reset creature strength for testing
	cout << "Would you like to set the creatures' strengths (for testing)?"
		<< endl;
	string menuItems[] = { "Yes", "No" };
	int menuChoice = menu(menuItems, 2, false);
	cout << endl;
	if (menuChoice == 1) // if user wants to set creature strength
	{
		cout << "Enter Creature 1->" << creat1->getName() << "'s new strength: ";
		creat1->setStrength(getInteger());
		cout << "Enter Creature 2->" << creat2->getName() << "'s new strength: ";
		creat2->setStrength(getInteger());
		cout << endl;
	}
}



//pit creatures against each other for a specified number of 
//matches and output the number of wins for each
void Combat::runTrials()
{
	int creat1Wins = 0;
	int creat2Wins = 0;
	int matchCounter = 0; //initialize round counter

	//prompt user for Creature 1 and Creature 2
	chooseCreatures();

	//choose number of matches
	cout << "Enter the number of matches (1-1000) to be played: ";
	int numMatches = getIntegerInRange(1, 1000);


	//loop through number of matches
	do
	{
		bool fightFinished = false;

		//randomly determine first attacker
		shared_ptr<Creature> attacker;
		shared_ptr<Creature> defender;
		if (getRandIntInRange(1, 2) == 1)
		{
			attacker = creat1;
			defender = creat2;
		}
		else
		{
			attacker = creat2;
			defender = creat1;
		}


		//loop until fight is finished
		do
		{
			//attString is value of attack roll or special ability
			string attString = attacker->attack();
			//defStrength is resulting strength after defense
			int defStrength = defender->defend(attString);


			//determine if fight is finished by checking defender's strength
			if (defStrength <= 0)
			{
				//output victory message
				fightFinished = true;

				if(attacker == creat1) //if creature 1 wins
				{
					creat1Wins++;
				}
				else //if creature 2 wins
				{
					creat2Wins++;
				}
			}

			else //get ready for next round
			{
				//swap attacker and defender
				shared_ptr<Creature> temp = attacker;
				attacker = defender;
				defender = temp;
			}

		} while (!fightFinished);

		matchCounter++; //increment match counter

		//return creatures to full health, lives and die multipliers
		creat1->refresh();
		creat2->refresh();

	} while (matchCounter < numMatches);

	//output results of trials
	cout << "Creature 1 (" << creat1->getName() << ") wins: " 
		<< creat1Wins << endl;
	cout << "Creature 2 (" << creat2->getName() << ") wins: " 
		<< creat2Wins << endl << endl;
}


Combat::Combat()
{
}


Combat::~Combat()
{
}


