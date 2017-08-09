// this is a header file for Creature.cpp

#ifndef MOON_CREATURE_HPP
#define MOON_CREATURE_HPP
#include "Die.hpp"
#include <string>
#include <sstream>
#include <memory>

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

	int row;
	int col;
	
public:
	virtual string attack();
	virtual int defend(string attString);
	void generateAttText(string special = "");
	void generateDefText(int prelimStrength, string special = "");
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
	string getAttText();
	string getDefText();

	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();

	virtual void refresh() = 0;

	Creature();
	virtual ~Creature() = 0;
};

#endif
