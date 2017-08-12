
#include <iostream>
#include <string>
#include "Map.hpp"
#include "Game.hpp"
#include "cs162_utilities.hpp"
#include "Hero.hpp"


using std::cout;
using std::endl;
using std::string;

int main()
{
	//set seed for RNG
	setSeed();

	//testing game logic menu

	//variables for amount of stone, wood and ore needed to build shelter
	int stoneNeeded = 7;
	int woodNeeded = 7;
	int oreNeeded = 7;
	shared_ptr<Creature>hero = 
		std::make_shared<Hero>(VILLAGE_ROW, VILLAGE_COL, 1000, 3, 3, 150);
	Game game(200, hero, stoneNeeded, woodNeeded, oreNeeded);
	game.gameLogic();



	return 0;

}

