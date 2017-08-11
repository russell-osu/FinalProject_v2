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
	village = new Village(VILLAGE_ROW,VILLAGE_COL, 7,7,7);
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
	this->movesRmn = maxMoves;
}


//handles primary game logic and play loop
void Game::gameLogic()
{
	//welcome message
	cout << "WELCOME TO RESOURCE QUEST!!" << endl;
	cout << "***************************" << endl << endl;
	map.dispMap();
	cout << endl;

	//for the game menu selection
	string menuChoice = "";



	//*********************MAIN PLAY LOOP***********************
	do
	{
		//var for curr spc creature
		shared_ptr<Creature> currCreat = currSpc->getCreat();

		//booleans for setting the type of space curr occupied
		bool isVillage = false;
		bool hasCreature = false;
		bool hasResources = false;

		//checks if current space is a village
		if (currSpc->getSpcTyp() == 'V')
		{
			isVillage = true;
		}

		//checks if current space has a creature
		if (currCreat != nullptr)
		{
			hasCreature = true;
		}

		//checks if current space has resources
		vector<shared_ptr<Item>> rscVect = currSpc->getRscItmVect();
		if (!rscVect.empty())
		{
			hasResources = true;
		}



		//output initial creature message (which includes hints about diff lvl)
		if(hasCreature)

		{
			cout << endl;
			cout << "You see " << currCreat->getName() << " eyeing you "
				"suspiciously from the edge of the " << currSpc->getName() <<
				"." << endl;

			int diffLvl = currSpc->getDiffLvl();
			switch(diffLvl)
			{
			case 1:
				cout << "You're close to the village. This creature may not"
					" pose much of a challenge." << endl << endl;
				break;
			case 2:
				cout << "You're a little far from home. It may be tough if you"
					" choose to fight." << endl << endl;
				break;
			case 3:
				cout << "You're at the edge of the known world. This creature"
					" might just eat your lunch." << endl << endl;
				break;

			}
		}



		//***************action menu items*************************
		vector<string> menuItems;
		menuItems.push_back("Move hero");
		menuItems.push_back("Display map");
		menuItems.push_back("Check inventory");


		//*************add other items based on conditions***************

		if (isVillage)//if curr spc is a village
		{
			menuItems.push_back("Build shelter");
		}

		
		else //if it's plains, forest, or hills
		{

			//if there are resources present, show gather rsc option
			if (hasResources)
			{
				menuItems.push_back("Gather resources");
			}

			//if a creature is present, show fight creature option
			if (hasCreature)
			{
				menuItems.push_back("Fight creature");
			}
		}
		menuItems.push_back("End game");


		//***********USER CHOICE***************
		cout << "What would you like to do?" << endl;
		menuChoice = menuRtnStr(menuItems, false);
		cout << endl;



		//*****************MENU CHOICE FLOW CONTROL******************

		//***MOVE HERO***
		if (menuChoice == "Move hero")
		{
			//clear screen and display map
			system("CLS"); 
			map.dispMap();

			//move hero
			moveHero();

			//clear screen and display map
			system("CLS"); 
			map.dispMap();
			
			//generate creature for recently entered space as long as it's
			//not a village, it doesn't already have a creature, and the 
			//number of total visits is less than 3;
			//if (currSpc->getSpcTyp() != 'V' && currCreat == nullptr 
			//	&& currSpc->getNumVisits() < 3)
			//{
			//	currSpc->genCreature();
			//}

			if (currSpc->getSpcTyp() != 'V')
			{
				currSpc->genCreature();
			}

			cout << "Num visits this space: " << currSpc->getNumVisits() << endl;
		}



		//***CHECK INVENTORY***
		else if (menuChoice == "Check inventory")
		{
			hero->chkInventory();
			cout << endl;
		}



		//***DISPLAY MAP***
		else if (menuChoice == "Display map")
		{
			system("CLS"); //clear screen
			map.dispMap();
		}


		//***GATHER RESOURCES***
		else if (menuChoice == "Gather resources")
		{
			//if there's no creature gathering is permitted

			if (currCreat == nullptr) 
			{
				currSpc->gatherRsc(hero);
				cout << endl;
			}
			else //if a creature is around, you'll have to fight it for rscs
			{
				cout << "If you want to gather resources, you'll have to"
					" fight the creature, first." << endl;
			}
		}


		//***FIGHT CREATURE***
		else if (menuChoice == "Fight creature")
		{
			//instantiate combat class
			Combat combat;
			//send hero and current spaces creature to combat
			shared_ptr<Creature> winner = combat.engage(hero, currCreat);

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


		//***BUILD SHELTER***
		else if (menuChoice == "Build shelter")
		{

			bool built = static_cast<Village*>(village)->buildShelter(hero);

			if(built)
			{
				cout << "You finished the shelter and saved the village!" 
					<< endl;
				cout << "*****************YOU WON!!!********************"
					<< endl << endl;
			}

		}


	} while (menuChoice != "End game"); 

	//********************end play loop**************************
}


void Game::moveHero()
{
	//get coor of currSpc
	int row = currSpc->getRow();
	int col = currSpc->getCol();
	
	//set currSpc to a temp pointer
	Space* tmpPrvSpc = currSpc;

	//set moved flag to false
	bool offMap = true;

	//prompt user for direction
	cout << "Which way would you like to move?" << endl;
	//string menuItems[] = { "North","South","East","West","Don't move"};
	//int menuChoice = menu(menuItems, 5, false);
	string usrIn = "";
	cout << "w) north" << endl << "s) south" << endl << "d) east" 
		<< endl << "a) west" << endl << endl << "x) don't move"<< endl << endl;
	getline(std::cin, usrIn);
	cout << endl;
	//validate usr input
	while (!(usrIn=="w"|| usrIn == "s" || usrIn == "d" || usrIn == "a" 
			|| usrIn == "x"))
	{
		cout << "Try again. Enter <w>, <s>, <d>, <a>, or <x>." << endl << endl;
		getline(std::cin, usrIn);
		cout << endl;
	}
	char menuChoice = usrIn[0]; //convert usrIn to char for switch



	switch(menuChoice)
	{
	case 'w': //North
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
				//set previous space North ptr to currSpc
				tmpPrvSpc->setNorth(spcArr[row - 1][col]);

			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row - 1][col];
			}
		}
		break; //case 1 break


	case 's': //South
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
				//set previous space South ptr to currSpc
				tmpPrvSpc->setSouth(spcArr[row + 1][col]);
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row + 1][col];
			}
		}
		break; //case 2 break

	case 'd': //East
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
				//set previous space East ptr to currSpc
				tmpPrvSpc->setEast(spcArr[row][col + 1]);
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row][col+1];
			}
		}
		break; //case 3 break


	case 'a': //West
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
				//set previous space West ptr to currSpc
				tmpPrvSpc->setWest(spcArr[row][col - 1]);
			}
			else //space already instantiated
			{
				//update curr space
				currSpc = spcArr[row][col - 1];
			}
		}
		break; //case 4 break

	case 'x': //Don't move
		offMap = false;


	}//end move choice switch

	if(offMap) //if hero tries to walk past edge of space array
	{
		cout << "You can't walk off of the edge of the known world!" 
			<< endl << endl;
		cout << "(press <enter> to continue)" << endl;
		std::cin.get();
	}
	else //increment number of visits to new currSpc
	{
		currSpc->incrementNumVisits();
	}

	tmpPrvSpc = nullptr;
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
