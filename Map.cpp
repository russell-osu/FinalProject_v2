#include "Map.hpp"
#include <iostream>
#include "defConst.hpp"

using std::cout;
using std::endl;




//default constructor for Map
Map::Map()
{
	//initialize map array with spaces
	for (int row = 0; row<29; row++)
	{
		for (int col = 0; col < 37; col++)
		{
			mapArr[row][col] = ' ';

		}

	}

	int rowCount = 0;

	//print single lined border rows every four "lines"
	for (int row = 0; row<29; row++)
	{
		for (int col = 0; col < 37; col++)
		{
			mapArr[row][col] = MAP_BORDER;
			rowCount++;
		}

		//skip three rows if one line of border has been printed

			row += 3;

	}

	int colCount = 0;

	//print double lined border columns every four "lines"
	for (int row = 0; row<29; row++)
	{
		for (int col = 0; col < 37; col++)
		{
			mapArr[row][col] = MAP_BORDER;
			colCount++;

			//skip three columns if two lines of border have been printed
			if (colCount % 2 == 0)
			{
				col += 3;
			}
		}
	}
}

//places the space type identifier in center of indicated map cell
void Map::updateMapSpc(int row, int col, char spcTyp)
{
	//find center of 3X3 map cell
	row = (row * 4) + 2; //extrapolate from space array to map
	col = (col * 5) + 3; //extrapolate from space array to map

	//put space type in map cell
	mapArr[row][col] = spcTyp;

}

//places a ring of asteriks around cell in indicate hero location
void Map::updateMapHero(int row, int col, int prvRow, int prvCol)
{
	//find center of 3X3 map cell
	row = (row * 4) + 2; //extrapolate from space array to map
	col = (col * 5) + 3; //extrapolate from space array to map
	prvRow = (prvRow * 4) + 2; //extrapolate from space array to map
	prvCol = (prvCol * 5) + 3; //extrapolate from space array to map

	//place asterik border around cell

	//top border
	for (int i = -1; i < 2; i++)
	{
		mapArr[row - 1][col + i] = HERO_BORDER;
	}

	//middle cells
	mapArr[row][col - 1] = HERO_BORDER;
	mapArr[row][col + 1] = HERO_BORDER;

	//bottom border
	for (int i = -1; i < 2; i++)
	{
		mapArr[row + 1][col + i] = HERO_BORDER;
	}

	//remove asterisk border from recently vacated cell

	//top border
	for (int i = -1; i < 2; i++)
	{
		mapArr[prvRow - 1][prvCol + i] = ' ';
	}

	//middle cells
	mapArr[prvRow][prvCol - 1] = ' ';
	mapArr[prvRow][prvCol + 1] = ' ';

	//bottom border
	for (int i = -1; i < 2; i++)
	{
		mapArr[prvRow + 1][prvCol + i] = ' ';
	}

}

//display map, map key, and hero stats
void Map::dispMap(int defSides, int numDefDie, int attSides, int numAttDie,
	int strength, int stoneWin, int stoneCnt, int woodWin, int woodCnt,
	int oreWin, int oreCnt)
{
	//print map
	for (int row = 0; row<29; row++)
	{
		for (int col = 0; col < 37; col++)
		{
			cout << mapArr[row][col];

		}
		switch(row)
		{
		case 0: cout <<"   V = Village (build shelter)";
			break;
		case 2: cout <<"   P = Plains (collect stone)";
			break;
		case 4: cout <<"   F = Forest (collect wood)";
			break;
		case 6: cout << "   H = Hills (collect ore)";
			break;
		case 8: cout <<"   *** = Hero location";
			break;
		case 12: cout << "   Hero Defense: " << numDefDie << "d" << defSides;
			break;
		case 13: cout << "   Hero Attack: " << numAttDie << "d" << attSides;
			break;
		case 14: cout << "   Hero Strength: " << strength;
			break;
		case 18: 	cout << "   Stone: " << stoneCnt << " of " <<
					stoneWin << " added to shelter";
			break;
		case 19: 	cout << "   Wood: " << woodCnt << " of " <<
					woodWin << " added to shelter";
			break;
		case 20: 	cout << "   Ore: " << oreCnt << " of " <<
					oreWin << " added to shelter";
			break;
		default:
			break;
		}
		cout << endl;
	}
}

Map::~Map()
{
}
