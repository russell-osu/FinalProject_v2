// this is a header file for Creature.cpp

#ifndef MOON_CREATURE_HPP
#define MOON_CREATURE_HPP
#include "Die.hpp"
#include <string>
#include <sstream>
#include <memory>
#include "Bag.hpp"

using std::string;
using std::stringstream;

class Creature
{
protected:
	std::shared_ptr<Die> attDie;
	std::shared_ptr<Die> defDie;
	int numAttDie; 
	int numDefDie; 
	int defRoll;
	int attRoll;
	int armor;
	int strength;
	string name;
	stringstream attText;
	stringstream defText;
	Bag bag;
	int startingStrength;

	int row;
	int col;
	
public:
	virtual string attack();
	virtual int defend(string attString);
	void generateAttText(string special = "");
	void generateDefText(int prelimStrength, string special = "");
	void chkInventory();
	bool addToBag(shared_ptr<Item> item, bool dispMsg=false);
	shared_ptr<Item> rmvFromBag();
	//shared_ptr<Item> rmvRscFromBag();


	//getters and setters
	void setNumAttDie(int numAttDie);
	int getNumAttDie();
	void setNumDefDie(int numDefDie);
	int getNumDefDie();
	void setArmor(int armor);
	int getArmor();
	void setStrength(int strength);
	int getStrength();
	void setName(string name);
	string getName();
	void setDefRoll(int defRoll);
	int getDefRoll();
	void setAttRoll(int attRoll);
	int getAttRoll();
	int getAttDieSides();
	int getDefDieSides();
	bool bagIsEmpty();
	string getAttText();
	string getDefText();
	Bag* getBag();


	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();

	virtual void refresh() = 0;

	Creature();
	Creature(int bagCapacity);
	virtual ~Creature() = 0;
};

#endif
