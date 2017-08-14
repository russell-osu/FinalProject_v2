
#include <iostream>
#include <string>
#include "Map.hpp"
#include "Game.hpp"
#include "cs162_utilities.hpp"
#include "Hero.hpp"
#include "asciiArt.hpp"


using std::cout;
using std::endl;
using std::string;

int main()
{
	//set seed for RNG
	setSeed();

	//welcome message and instructions.

	//welcome message
	asciiVillNoShelter();
	cout << "                     RESOURCE QUEST!!!" << endl;
	cout << "************************************************************" 
		<< endl;
	cout << "Welcome, brave gatherer! You are the Hero of a poor village,\n"
		"an isolated hamlet beset on all sides by monsters. Recently,\n"
		"a fire swept through village, destroying everything larger than\n"
		"an outhouse. You must travel into the dangerous lands beyond\n"
		"the village. You will collect resources for the construction of a\n"
		"temporary shelter where your people can take refuge from the\n"
		"terrors of the night. Visit Plains, to collect stone,\n"
		"Forests, to collect wood, and Hills, to collect ore. When you have\n"
		"collected resources, return to the village to add them to the\n"
		"shelter. Venture out and return as often as needed. The further\n"
		"a region is from the village, the more resources you'll find, but\n"
		"the monsters will also be harder."<< endl << endl; 
		
	cout << "When the shelter is built, you've won the game! Don't\n"
		"fall prey to monsters along the way. Also, stay mindful of time.\n"
		"If you take too long, your village will succumb to the terrors\n"
		"of the night."<<endl<< endl; 


	//create menu and prompt user for game difficulty
	string menuItems[] = { "Easy", "Medium", "Hard", "End program" };
	int menuChoice = 0;

	//create variables for game instantiation
	int strength, attDie, defDie, bagCap, moves, stone, wood, ore;
	
	do
	{

		cout << "Choose a difficulty level to start a new game "
			"(or <End program> to exit)." << endl;
		menuChoice = menu(menuItems, 4, false);
		cout << endl;

		//set initialization variables
		if (menuChoice == 1) //easy
		{
			strength = 2000;
			attDie = 5;
			defDie = 5;
			bagCap = 150;
			moves = 1000;
			stone = 5;
			wood = 5;
			ore = 5;
		}
		else if (menuChoice == 2) //medium
		{
			strength = 1000;
			attDie = 4;
			defDie = 4;
			bagCap = 75;
			moves = 250;
			stone = 7;
			wood = 7;
			ore = 7;
		}
		else if (menuChoice == 3) //hard
		{
			strength = 1000;
			attDie = 3;
			defDie = 3;
			bagCap = 10;
			moves = 30;
			stone = 10;
			wood = 10;
			ore = 10;
		}

		if(menuChoice != 4)
		{
			//instantiate Game based on initialization variables
			shared_ptr<Creature>hero =
				std::make_shared<Hero>(VILLAGE_ROW, VILLAGE_COL,
					strength, attDie, defDie, bagCap);
			Game game(moves, hero, stone, wood, ore);
			game.gameLogic();
			
		}

	} while (menuChoice != 4);


	return 0;

}

