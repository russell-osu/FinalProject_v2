
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
	////testing the map
	//Map map;

	//map.updateMapSpc(3, 3, 'V');
	//map.dispMap();
	//cout << endl;
	//map.updateMapHero(3, 3);
	//map.dispMap();
	//cout << endl;
	//map.updateMapHero(3, 4, 3, 3);
	//map.dispMap();
	//cout << endl;

	//set seed
	setSeed();

	//testing game logic menu
	Creature* hero = new Hero(VILLAGE_ROW, VILLAGE_COL, 35, 3, 3);
	Game game(100,hero);
	game.gameLogic();



	return 0;

}

