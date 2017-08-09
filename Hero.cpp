#include "Hero.hpp"




//default constructor with default coord of (3,3) and 25 str
Hero::Hero()
{
	this->row = 3;
	this->col = 3;
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(10);
	numAttDie = 2;
	numDefDie = 2;
	armor = 0;
	strength = 25;
	startingStrength = 25;
	name = "Hero";
}

//constructor that takes coord parameters
Hero::Hero(int row, int col, int strength, int numAttDie, int numDefDie)
{
	this->row = row;
	this->col = col;
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(10);
	this->numAttDie = numAttDie;
	this->numDefDie = numDefDie;
	armor = 0;
	this->strength = strength;
	startingStrength = strength;
	name = "Hero";
}


void Hero::refresh()
{
	strength = startingStrength;
}

Hero::~Hero()
{
}
