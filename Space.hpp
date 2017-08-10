// this is a header file for Space.cpp

#ifndef MOON_SPACE_HPP
#define MOON_SPACE_HPP
#include "Creature.hpp"
#include <vector>
#include "Item.hpp"


using std::shared_ptr;
using std::vector;

class Space
{
protected:
	int row;
	int col;
	Creature* creat;
	char spcTyp;

	//for stone, wood, and ore (resources)
	vector<shared_ptr<Item>> rscItmVect;
	//for all other items
	vector<shared_ptr<Item>> miscItmVect;

	int diffLvl;


	//map pointers
	Space* north;
	Space* south;
	Space* east;
	Space* west;


public:
	Space();

	void genResources();
	void setDifficulty();
	virtual int gatherRsc();
	virtual string describe() = 0;
	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();
	void setCreat(Creature* creat);
	Creature* getCreat();
	void setSpcTyp(char spcTyp);
	char getSpcTyp();
	void setDiffLvl(int diffLvl);
	int getDiffLvl();

	//map pointer getters and setters
	void setNorth(Space* north);
	Space* getNorth();

	void setSouth(Space* south);
	Space* getSouth();

	void setEast(Space* east);
	Space* getEast();

	void setWest(Space* west);
	Space* getWest();


	virtual ~Space();
};

#endif