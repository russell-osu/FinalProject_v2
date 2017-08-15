// this is a header file for Space.cpp

#ifndef MOON_SPACE_HPP
#define MOON_SPACE_HPP
#include "Creature.hpp"
#include <vector>
#include "Item.hpp"


class Hero;
using std::shared_ptr;
using std::vector;

class Space
{
protected:
	int row;
	int col;
	shared_ptr<Creature> creat;
	char spcTyp;
	string name;
	int numVisits;

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
	void dispRscItmVect();
	void setDifficulty();
	bool gatherRsc(shared_ptr<Creature>hero);
	void rmvVectItm(vector<shared_ptr<Item>>&, int itmToRmv);
	void addRscItm(shared_ptr<Item>item);
	void addMiscItm(shared_ptr<Item>item);
	void genCreature();
	void genCreatItems();
	void incrementNumVisits();
	virtual string describe() = 0;
	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();
	void setCreat(shared_ptr<Creature> creat);
	shared_ptr<Creature> getCreat();
	void setSpcTyp(char spcTyp);
	char getSpcTyp();
	void setDiffLvl(int diffLvl);
	int getDiffLvl();
	void setName(string name);
	string getName();
	void setNumVisits(int numVisits);
	int getNumVisits();
	vector<shared_ptr<Item>>& getRscItmVect();

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