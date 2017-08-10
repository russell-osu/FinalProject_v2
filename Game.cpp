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


Game::Game(int maxMoves, shared_ptr<Creature>hero)
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
		menuItems.push_back("Display map");
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
		cout << endl;


		//menuChoice flow control
		if (menuChoice == "Move hero")
		{

			moveHero();
			system("CLS"); //clear screen
			map.dispMap();
			
			//generate creature for recently entered space as long as it's
			//not a village
			if (currSpc->getSpcTyp() != 'V')
			{
				currSpc->genCreature();
			}




		}

		else if (menuChoice == "Check inventory")
		{
			hero->chkInventory();
			cout << endl;
		}

		else if (menuChoice == "Display map")
		{
			system("CLS"); //clear screen
			map.dispMap();
		}

		else if (menuChoice == "Gather resources")
		{
			currSpc->gatherRsc(hero);
			cout << endl;
		}

		else if (menuChoice == "Fight creature")
		{
			//instantiate combat class
			Combat combat;
			//send hero and current spaces creature to combat
			shared_ptr<Creature> winner = combat.engage(hero, currSpc->getCreat());

			//if hero wins, set curr spac creature to nullptr
			if(winner->getName() == "Hero")
			{
				currSpc->setCreat(nullptr);
			}
			else //if hero loses, game is over
			{
				menuChoice = "End game";
				cout << "The hero has succumbed to the creature." << endl;
				cout << "**************GAME OVER****************" << endl
					<< endl;
			}


		}



	} while (menuChoice != "End game");
}


void Game::moveHero()
{
	//get coor of currSpc
	int row = currSpc->getRow();
	int col = currSpc->getCol();
	
	//set moved flag to false
	bool offMap = true;

	//prompt user for direction
	cout << "Which way would you like to move?" << endl;
	string menuItems[] = { "North","South","East","West","Don't move"};
	int menuChoice = menu(menuItems, 5, false);

	switch(menuChoice)
	{
	case 1: //North
		if (row > 0)//to prevent hero from going off of the board
		{
			offMap = false; 

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
			offMap = false;

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
			offMap = false;

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
			offMap = false;

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

	case 5: //Don't move
		offMap = false;


	}//end move choice switch

	if(offMap) //if hero tries to walk past edge of space array
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
