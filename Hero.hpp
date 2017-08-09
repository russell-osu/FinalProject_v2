// this is a header file for Hero.cpp

#ifndef MOON_HERO_HPP
#define MOON_HERO_HPP
#include "Creature.hpp"

class Hero : public Creature
{

private:
	//Bag bag
	int startingStrength;

public:
	Hero();
	Hero(int row, int col, int strength, int numAttDie, int numDefDie);
	virtual void refresh();
	~Hero();
};

#endif
