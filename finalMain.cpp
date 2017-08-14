
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
		"shelter. Venture out and return as often as needed." << endl << endl; 
		
	cout << "When the shelter is built, you've won the game! Don't\n"
		"fall prey to monsters along the way. Also, stay mindful of time.\n"
		"If you take too long, your village will succumb to the terrors\n"
		"of the night."<<endl<< endl; 


	//create menu and prompt user for game difficulty
	string menuItems[] = { "Easy", "Medium", "Hard", "End program" };
	int menuChoice = 0;

	do
	{

		cout << "Choose a difficulty level to start a new game "
			"(or <End program> to exit)." << endl;
		menuChoice = menu(menuItems, 4, false);
		cout << endl;

		if (menuChoice == 1)
		{
			shared_ptr<Creature>hero =
				std::make_shared<Hero>(VILLAGE_ROW, VILLAGE_COL, 2000, 5, 5, 150);
			Game game(1000, hero, 5, 5, 5);
			game.gameLogic();
		}
		else if (menuChoice == 2)
		{
			shared_ptr<Creature>hero =
				std::make_shared<Hero>(VILLAGE_ROW, VILLAGE_COL, 1000, 4, 4, 75);
			Game game(500, hero, 10, 10, 10);
			game.gameLogic();
		}
		else if (menuChoice == 3)
		{
			shared_ptr<Creature>hero =
				std::make_shared<Hero>(VILLAGE_ROW, VILLAGE_COL, 500, 3, 3, 50);
			Game game(12, hero, 15, 15, 15);
			game.gameLogic();
		}

	} while (menuChoice != 4);


	return 0;

}

