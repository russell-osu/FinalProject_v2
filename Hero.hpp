// this is a header file for Hero.cpp

#ifndef MOON_HERO_HPP
#define MOON_HERO_HPP
#include "Creature.hpp"
#include "Bag.hpp"

class Hero : public Creature
{

private:
	//Bag bag;
	//int startingStrength;

public:
	Hero();
	Hero(int row, int col, int strength, int numAttDie, int numDefDie,
		int bagCapacity);
	virtual void refresh();
	//void chkBag();
	//bool addToBag(shared_ptr<Item> item);
	~Hero();
};

#endif
