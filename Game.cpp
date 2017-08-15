#include "Game.hpp"
#include "Village.hpp"
#include "Hero.hpp"
#include <iostream>
#include <string>
#include "cs162_utilities.hpp"
#include "Plains.hpp"
#include "Forest.hpp"
#include "Hills.hpp"
#include "asciiArt.hpp"

using std::cout;
using std::endl;
using std::string;

char prmptUsrMv();
void createActionMenu(vector<string>& menuItems, bool isVillage, 
	bool hasCreature, bool hasResources);


Game::Game(int maxMoves, shared_ptr<Creature>hero, 
	int stone, int wood, int ore)
{
	//set all elements in spcArr to nullptr
	for (int row=0; row<SPC_ROWS; row++)
	{
		for(int col=0; col<SPC_COLS; col++)
		{
			spcArr[row][col] = nullptr;
		}
	}

	//set resources needed for win
	stoneWin = stone;
	woodWin = wood;
	oreWin = ore;

	//instantiate village and point given space array cell to village
	//pass amt of stone, wood, and ore needed to build shelter
	village = new Village(VILLAGE_ROW,VILLAGE_COL, stoneWin, woodWin, oreWin);
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

	//clear screen, display map and display village msg
	system(CLEAR_SCREEN);
	map.dispMap(hero, village);
	dispSpcMsg();
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


		//create game action menu
		vector<string> menuItems;
		createActionMenu(menuItems, isVillage, hasCreature, hasResources);


		//***********USER CHOICE***************

		//check moves remaining
		if (movesRmn <= 0) //if player has run out of moves
		{
			//set end game condition
			menuChoice = "End game";

			cout << "You have run out of moves." << endl;
			cout << "(press <enter> to continue)" << endl;
			std::cin.ignore(INT_MAX, '\n');
			//clear screen and output lose message
			system(CLEAR_SCREEN);
			asciiYouLose();
			cout << "You have run out of moves. The village has succumbed\n"
				"to the terrors of the night." << endl;
			cout << "**********************GAME OVER***********************"
				<< endl << endl;;
		}

		else //prompt user for menu choice
		{
			cout << "What would you like to do?" << endl;
			menuChoice = menuRtnStr(menuItems, false);
			cout << endl;
		}


		//*****************MENU CHOICE FLOW CONTROL******************

		bool sufficientMoves = false;


		//***MOVE HERO***
		if (menuChoice == "Move hero" && movesRmn > 0)
		{
			sufficientMoves = true; //enough moves left for this action
			//clear screen and display map
			system(CLEAR_SCREEN); 
			map.dispMap(hero, village);

			//move hero
			moveHero();

		}



		//**********CHECK BAG**********
		else if (menuChoice == "Check bag")
		{
			sufficientMoves = true;//enough moves left for this action
			//clear screen
			system(CLEAR_SCREEN);
			//check inventory
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
			hero->chkBag();
=======
			hero->chkInventory();
>>>>>>> parent of ecc67e4... working--about to implement use item
=======
			hero->chkInventory();
>>>>>>> parent of ecc67e4... working--about to implement use item
=======
			hero->chkInventory();
>>>>>>> parent of ecc67e4... working--about to implement use item
=======
			hero->chkInventory();
>>>>>>> parent of ecc67e4... working--about to implement use item

			Bag* heroBag = hero->getBag();
			//present option to rmv item from bag if bag is not empty
			if (!heroBag->getBagVect().empty())
			{
				string menuItems[] = { "yes", "no" };
				cout << "Remove an item from the bag?" << endl;
				int menuChoice = menu(menuItems, 2, false);
				cout << endl;
				//place item in one pf curr space's vectors (rsc or misc)
				shared_ptr<Item>itmToRmv;
				if (menuChoice == 1)
				{
					itmToRmv = hero->rmvFromBag();
					
					//add item to curr space's rsc vector if rsc
					if(itmToRmv->getSubclass() == "resource")
					{
						currSpc->addRscItm(itmToRmv);
					}
					//add item to curr spc's misc vect if not rsc
					else
					{
						currSpc->addMiscItm(itmToRmv);
					}
				}
			}


<<<<<<< HEAD
			pauseTillEnter();
=======
			pauseUntilEnter();
>>>>>>> parent of ecc67e4... working--about to implement use item
			system(CLEAR_SCREEN);//clear screen
			map.dispMap(hero, village); //display map
			dispSpcMsg();//display current spaces message
		}



		//***DISPLAY MAP***
		else if (menuChoice == "Display map")
		{
			sufficientMoves = true;//enough moves left for this action
			system(CLEAR_SCREEN);//clear screen
			map.dispMap(hero, village); //display map
			dispSpcMsg();//display current spaces message
		}


		//***GATHER RESOURCES***
		else if (menuChoice == "Gather resources" && movesRmn > 1)
		{
			sufficientMoves = true;//enough moves left for this action
			//if there's no creature gathering is permitted

			if (currCreat == nullptr) 
			{
				system(CLEAR_SCREEN);//clear screen
				map.dispMap(hero, village); //display map

				currSpc->gatherRsc(hero);
				
				system(CLEAR_SCREEN);//clear screen
				map.dispMap(hero, village); //display map
				dispSpcMsg();//display current spaces message

				//gathering resources requires two moves
				updMovesRmn(2);
			}
			else //if a creature is around, you'll have to fight it for rscs
			{
				system(CLEAR_SCREEN);//clear screen
				map.dispMap(hero, village); //display map
				dispSpcMsg();//display current spaces message
				cout << "If you want to gather resources, you'll have to"
					" fight the creature, first." << endl << endl;
			}
		}


		//***FIGHT CREATURE***
		else if (menuChoice == "Fight creature" && movesRmn > 2)
		{
			sufficientMoves = true;//enough moves left for this action
			system(CLEAR_SCREEN);//clear screen

			//instantiate combat class
			Combat combat;
			//send hero and current spaces creature to combat
			shared_ptr<Creature> winner = combat.engage(hero, currCreat);

			//fighting requires four moves
			updMovesRmn(3);

			//if hero wins, set curr spac creature to nullptr
			if(winner->getName() == "Hero")
			{
				currSpc->setCreat(nullptr);
				pauseTillEnter();
				system(CLEAR_SCREEN);
				map.dispMap(hero, village);
				dispSpcMsg();
			}
			else //if hero loses, game is over
			{
				menuChoice = "End game";
				pauseTillEnter();

				//clear screen and output lose message
				system(CLEAR_SCREEN);
				asciiYouLose();
				cout << "The hero has succumbed to the creature." << endl;
				cout << "***************GAME OVER***************" << endl
					<< endl;
			}
		}


		//***ADD RESOURCES TO SHELTER***
		else if (menuChoice == "Add resources to shelter" && movesRmn > 2)
		{
			sufficientMoves = true;//enough moves left for this action
			system(CLEAR_SCREEN);

			bool built = static_cast<Village*>(village)->buildShelter(hero);

			//building shelter requires 2 moves
			updMovesRmn(2);

			if(built)
			{
				cout << "You have fulfilled your mission..." << endl;
				pauseTillEnter(); //pause
				system(CLEAR_SCREEN);//clear screen

				//output ascii shelter and win message
				asciiShelter();

				cout << "By supplying the necessary resources, "
					"you saved the village!" 
					<< endl;
				cout << "******************YOU WON!!!********************"
					<< endl << endl;

				//end game
				menuChoice = "End game";
			}

		}


		/******READ INSTRUCTIONS******/
		//Display game instructions
		if (menuChoice == "Read instructions")
		{
			sufficientMoves = true;//enough moves left for this action
			dispInstructions();
		}


		/******MOVE CHECKER******/
		//if hero does not have sufficient moves for action chosen
		if(sufficientMoves == false && menuChoice!="End game")
		{
			cout << "You don't have enough moves left for that action."
				<< endl << endl;;
		}

	} while (menuChoice != "End game"); 

	//********************end play loop**************************
}



/******************CREATE ACTION MENU************************/
void createActionMenu(vector<string>& menuItems, bool isVillage, 
	bool hasCreature, bool hasResources)
{
	menuItems.push_back("Move hero");
	menuItems.push_back("Display map");
	menuItems.push_back("Check bag");


	//*************add other items based on conditions***************

	if (isVillage)//if curr spc is a village
	{
		menuItems.push_back("Add resources to shelter");
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

	//add items at end of list
	menuItems.push_back("Read instructions");
	menuItems.push_back("End game");
}


/*****************UPDATE REMAINING MOVES*********************/
void Game::updMovesRmn(int newMoves)
{
	movesRmn -= newMoves;
}



/***********************PROMPT USER MOVE CHOICE**********************/
//prompts for and returns usr mvmt choice
char prmptUsrMv()
{
	string usrIn;
	
	//prompt user for direction
	cout << "Which way would you like to move?" << endl;

	cout << "w) north" << endl << "s) south" << endl << "d) east"
		<< endl << "a) west" << endl << endl << "x) Open the action"
		" menu for this area." << endl << endl;
	getline(std::cin, usrIn);
	cout << endl;
	//validate usr input
	while (!(usrIn == "w" || usrIn == "s" || usrIn == "d" || usrIn == "a"
		|| usrIn == "x"))
	{
		cout << "Try again. Enter <w>, <s>, <d>, <a>, or <x>." << endl << endl;
		getline(std::cin, usrIn);
		cout << endl;
	}

	return usrIn[0];
}



/*********************MOVE HERO*************************/
//moves hero until user chooses to exit move interface
void Game::moveHero()
{
	char menuChoice;

	//loop wsda menu options until user chooses to not move
	do
	{
		//get coor of currSpc
		int row = currSpc->getRow();
		int col = currSpc->getCol();

		//set currSpc to a temp pointer
		Space* tmpPrvSpc = currSpc;

		//set moved flag to false
		bool offMap = true;

		//returns user mvmt choice
		menuChoice = prmptUsrMv();

		//switch statment for processing user mvmt choice
		switch (menuChoice)
		{
		case 'w': //North
			if (row > 0)//to prevent hero from going off of the board
			{
				offMap = false;
				//moving hero requires one move
				updMovesRmn(1);
				//update hero on map
				map.updateMapHero(row - 1, col, row, col);

				//update hero coord
				hero->setRow(row - 1);
				hero->setCol(col);

				//instantiate new spc if not instantiated and add spc type to map
				if (currSpc->getNorth() == nullptr)//if curr spc not instatiated
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
				//moving hero requires one move
				updMovesRmn(1);
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
				//moving hero requires one move
				updMovesRmn(1);
				//update hero on map
				map.updateMapHero(row, col + 1, row, col);

				//update hero coord
				hero->setRow(row);
				hero->setCol(col + 1);

				//instantiate new spc if not instantiated and add spc type to map
				if (currSpc->getEast() == nullptr)//if curr spc not instatiated
				{
					//instantiate new space
					newSpcInit(row, col + 1);
					//update curr space
					currSpc = spcArr[row][col + 1];
					//set previous space East ptr to currSpc
					tmpPrvSpc->setEast(spcArr[row][col + 1]);
				}
				else //space already instantiated
				{
					//update curr space
					currSpc = spcArr[row][col + 1];
				}
			}
			break; //case 3 break


		case 'a': //West
			if (col > 0)//to prevent hero from going off of the board
			{
				offMap = false;
				//moving hero requires one move
				updMovesRmn(1);
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
			//clear screen, display map and display spc msg
			system(CLEAR_SCREEN);
			map.dispMap(hero, village);
			dispSpcMsg();
		}//end move choice switch



		if (offMap) //if hero tries to walk past edge of space array
		{
			cout << "You can't walk off of the edge of the known world!"
				<< endl << endl;
			cout << "(press <enter> to continue)" << endl;

			//pause until user presses enter, courtesy of
			//https://stackoverflow.com/questions/257091/
			//how-do-i-flush-the-cin-buffer
			std::cin.ignore(INT_MAX,'\n');
			

		}
		
		else if (!offMap && menuChoice != 'x')//if hero moves
		{
			//perform post-movement operations
			postMoveOp();
		}


		tmpPrvSpc = nullptr; //set prv spc to nullptr

	}while (menuChoice != 'x' && movesRmn > 0); //end move loop
}




/*********************POST-MOVEMENT OPERATIONS*********************/
//operations to perform after hero moves to a new space
void Game::postMoveOp()
{
	//increment number of visits to space
	currSpc->incrementNumVisits();

	//clear screen and display map
	system(CLEAR_SCREEN);
	map.dispMap(hero, village);

	//generate new creature if currSpc not village

	if (currSpc->getSpcTyp() != 'V')
	{
		currSpc->genCreature();
	}

	//display space message
	dispSpcMsg();
}


/*************************SPACE MESSAGE*************************/
//generates msg to disp for current space
void Game::dispSpcMsg()
{

	//var for curr spc creature
	shared_ptr<Creature> currCreat = currSpc->getCreat();

	//*****output info about moves, difficulty of region and*****
	//*****resources available (if not a village)****************
	cout << "Moves remaining: " << movesRmn << endl;
	cout << "Region difficulty: " << currSpc->getDiffLvl() << endl;
	if (currSpc->getSpcTyp() != 'V')
	{
		cout << "Resource status: ";
		if (currSpc->getRscItmVect().empty())
		{
			cout << "ALL GATHERED" <<endl<<endl;
		}
		else
		{
			cout << "RESOURCES PRESENT" << endl << endl;
		}
	}
	else
	{
		cout << endl;
	}

	
	if (currCreat != nullptr) //if a creature is in the space
	{
		cout << "You see " << currCreat->getName() << " eyeing you "
			"suspiciously from the edge of the " << currSpc->getName() <<
			"." << endl;

		//output message predicated on space difficulty level
		int diffLvl = currSpc->getDiffLvl();
		switch (diffLvl)
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

	//if current space is a village
	if (currSpc->getSpcTyp() == 'V')
	{
		//static_cast<Village*>(village)->dispSheltRsc();
		cout << "You're in the village. If you have any resources, you\n"
			"could add them to the shelter." << endl << endl;
	}
}


//displays game instructions
void Game::dispInstructions()
{
	system(CLEAR_SCREEN);

	cout << "                     INSTRUCTIONS" << endl;
	cout << "************************************************************"
		<< endl;
	cout << "You must travel into the dangerous lands beyond the village\n"
		"and collect resources for the construction of a temporary\n"
		"but secure shelter. Visit Plains, to collect stone, Forests,\n"
		"to collect wood, and Hills, to collect ore. When you have\n"
		"collected resources, return to the village to add them to the\n"
		"shelter. Venture out and return as often as needed. The further\n"
		"a region is from the village, the more resources you'll find, but\n"
		"the monsters will also be harder." << endl << endl;

	cout << "When the shelter is built, you've won the game! Don't\n"
		"fall prey to monsters along the way. Also, stay mindful of time.\n"
		"If you take too long, your village will succumb to the terrors\n"
		"of the night." << endl << endl;

	cout << "(press <enter> to continue)" << endl;
	std::cin.ignore(INT_MAX, '\n');

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


																		
//deallocates pointers in space array
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
