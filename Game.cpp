#include "Game.hpp"
#include "Village.hpp"
#include "Hero.hpp"
#include <iostream>
#include <string>
#include "cs162_utilities.hpp"
#include "Plains.hpp"
#include "Forest.hpp"
#include "Hills.hpp"

using std::cout;
using std::endl;
using std::string;


Game::Game(int maxMoves, Creature* hero)
{
	//set all elements in spcArr to nullptr
	for (int row=0; row<SPC_ROWS; row++)
	{
		for(int col=0; col<SPC_COLS; col++)
		{
			spcArr[row][col] = nullptr;
		}
	}

	//instantiate village and point given space array cell to village
	village = new Village(VILLAGE_ROW,VILLAGE_COL);
	spcArr[VILLAGE_ROW][VILLAGE_COL] = village;

	//instantiate hero and place in village
	this->hero = hero;

	//add village to map and place hero on map
	map.updateMapSpc(VILLAGE_ROW, VILLAGE_COL, village->getSpcTyp());
	map.updateMapHero(hero->getRow(), hero->getCol());


	//set current space to village
	currSpc = village;

	//set max moves
	this->maxMoves = maxMoves;

	//initialize number of moves to 0
	this->numMoves = 0;
}

void Game::gameLogic()
{
	//welcome message
	cout << "WELCOME TO RESOURCE QUEST!!" << endl;
	cout << "***************************" << endl << endl;
	map.dispMap();
	cout << endl;

	//booleans for setting the type of space curr occupied
	bool isVillage;
	bool hasCreature;

	string menuChoice = "";

	//main play loop
	do
	{
		//checks if current space is a village
		if (currSpc->getSpcTyp() == 'V')
		{
			isVillage = true;
		}
		else
		{
			isVillage = false;
		}

		//checks if current space has a creature
		if (currSpc->getCreat() == nullptr)
		{
			hasCreature = false;
		}
		else
		{
			hasCreature = true;
		}


		//action menu items
		vector<string> menuItems;
		menuItems.push_back("Move hero");
		menuItems.push_back("Check inventory");
		if (isVillage)//if curr spc is a village
		{
			menuItems.push_back("Build shelter");
		}
		else //if it's plains, forest, or hills
		{
			menuItems.push_back("Gather resources");

			if (hasCreature)
			{
				menuItems.push_back("Fight creature");
			}
		}
		menuItems.push_back("End game");


		//prompt for and store user choice
		cout << "What would you like to do?" << endl;
		menuChoice = menuRtnStr(menuItems, false);


		//menuChoice control flow
		if (menuChoice == "Move hero")
		{
			moveHero();
			map.dispMap();
			cout << "Diff Lvl: " << currSpc->getDiffLvl() << endl;
		}

	} while (menuChoice != "End game");
}


void Game::moveHero()
{
	//get coor of currSpc
	int row = currSpc->getRow();
	int col = currSpc->getCol();
	
	//set moved flag to false
	bool moved = false;

	//prompt user for direction
	string menuItems[] = { "North","South","East","West" };
	int menuChoice = menu(menuItems, 4, false);

	switch(menuChoice)
	{
	case 1: //North
		if (row > 0)//to prevent hero from going off of the board
		{
			moved = true; 

			//update hero on map
			map.updateMapHero(row - 1, col, row, col);

			//update hero coord
			hero->setRow(row - 1);
			hero->setCol(col);

			//instantiate new spc if not instantiated and add spc type to map
			if(currSpc->getNorth() == nullptr)//if curr spc not instatiated
			{
				//instantiate new space
				newSpcInit(row - 1, col);
				//update curr space
				currSpc = spcArr[row - 1][col];
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row - 1][col];
			}
		}
		break; //case 1 break


	case 2: //South
		if (row < 6)//to prevent hero from going off of the board
		{
			moved = true;

			//update hero on map
			map.updateMapHero(row + 1, col, row, col);

			//update hero coord
			hero->setRow(row + 1);
			hero->setCol(col);

			//instantiate new spc if not instantiated and add spc type to map
			if (currSpc->getSouth() == nullptr)//if curr spc not instatiated
			{
				//instantiate new space
				newSpcInit(row + 1, col);
				//update curr space
				currSpc = spcArr[row + 1][col];
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row + 1][col];
			}
		}
		break; //case 2 break

	case 3: //East
		if (col < 6)//to prevent hero from going off of the board
		{
			moved = true;

			//update hero on map
			map.updateMapHero(row, col+1, row, col);

			//update hero coord
			hero->setRow(row);
			hero->setCol(col+1);

			//instantiate new spc if not instantiated and add spc type to map
			if (currSpc->getEast() == nullptr)//if curr spc not instatiated
			{
				//instantiate new space
				newSpcInit(row, col+1);
				//update curr space
				currSpc = spcArr[row][col+1];
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row][col+1];
			}
		}
		break; //case 3 break


	case 4: //West
		if (col > 0)//to prevent hero from going off of the board
		{
			moved = true;

			//update hero on map
			map.updateMapHero(row, col - 1, row, col);

			//update hero coord
			hero->setRow(row);
			hero->setCol(col - 1);

			//instantiate new spc if not instantiated and add spc type to map
			if (currSpc->getWest() == nullptr)//if curr spc not instatiated
			{
				//instantiate new space
				newSpcInit(row, col - 1);
				//update curr space
				currSpc = spcArr[row][col - 1];
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row][col - 1];
			}
		}
		break; //case 4 break

	}//end move choice switch

	if(!moved) //if hero tries to walk past edge of space array
	{
		cout << "You can't walk off of the edge of the known world!" 
			<< endl << endl;
	}
}


//initializes a space with a randomly choice space subclass
void Game::newSpcInit(int row, int col)
{
	Space* tmpSpc;
	int randSpc = getRandIntInRange(1, 3);

	switch(randSpc)
	{
	case 1: //Plains
		//initialize randomly chose subclass of Space
		tmpSpc = new Plains(row, col);
		//point space array cell to tmp
		spcArr[row][col] = tmpSpc;
		//update map with space type
		map.updateMapSpc(row, col, tmpSpc->getSpcTyp());
		//connct pointers in new space to other, surrounding instantiated spcs
		newSpcConnect(tmpSpc);
		//set tmpSpc to nullptr
		break;

	case 2: //Forest
		//initialize randomly chose subclass of Space
		tmpSpc = new Forest(row, col);
		//point space array cell to tmp
		spcArr[row][col] = tmpSpc;
		//update map with space type
		map.updateMapSpc(row, col, tmpSpc->getSpcTyp());
		//connct pointers in new space to other, surrounding instantiated spcs
		newSpcConnect(tmpSpc);
		//set tmpSpc to nullptr
		break;


	case 3: //Hills
		//initialize randomly chose subclass of Space
		tmpSpc = new Hills(row, col);
		//point space array cell to newly instantiated object
		spcArr[row][col] = tmpSpc;
		//update map with space type
		map.updateMapSpc(row, col, tmpSpc->getSpcTyp());
		//connct pointers in new space to other, surrounding instantiated spcs
		newSpcConnect(tmpSpc);
		//set tmpSpc to nullptr
		break;
	} //end switch

	tmpSpc = nullptr;
}


//connct pointers in new space to other, surrounding instantiated spcs
void Game::newSpcConnect(Space* tmpSpc)
{
	//get coord of new space to be connected to its surroundings
	int row = tmpSpc->getRow();
	int col = tmpSpc->getCol();

	//set north, south, east and west pointers if those spaces have already
	//been instantiated

	//set north
	if(spcArr[row-1][col]!=nullptr)
	{
		tmpSpc->setNorth(spcArr[row - 1][col]);
	}

	//set south
	if (spcArr[row + 1][col] != nullptr)
	{
		tmpSpc->setSouth(spcArr[row + 1][col]);
	}

	//set east
	if (spcArr[row][col+1] != nullptr)
	{
		tmpSpc->setEast(spcArr[row][col+1]);
	}

	//set west
	if (spcArr[row][col - 1] != nullptr)
	{
		tmpSpc->setWest(spcArr[row][col - 1]);
	}

}


Game::~Game()
{
	currSpc = nullptr;
	village = nullptr;

	//free memory in space array
	for (int row = 0; row<SPC_ROWS; row++)
	{
		for (int col = 0; col<SPC_COLS; col++)
		{
			//check to see if cell points to a space
			if (spcArr[row][col] != nullptr)
			{
				//set pointers to other regions to nullptr
				spcArr[row][col]->setNorth(nullptr);
				spcArr[row][col]->setSouth(nullptr);
				spcArr[row][col]->setEast(nullptr);
				spcArr[row][col]->setWest(nullptr);

				//free ptr
				delete spcArr[row][col];
				spcArr[row][col] = nullptr;
			}
		}
	}
}
