/******************************************************************************
Class: Hero
Name: Russell Moon
Date: 8/12/2017
Description: A subclass of Creature which represents the players character
in the game.
******************************************************************************/

#include "Hero.hpp"
#include<iostream>

using std::cout;
using std::endl;


//default constructor with default coord of (3,3) and 25 str
Hero::Hero()
{
	this->row = 3;
	this->col = 3;
	attDie = std::make_shared<Die>(10);
	defDie = std::make_shared<Die>(10);
	numAttDie = 2;
	numDefDie = 2;
	armor = 10;
	strength = 25;
	startingStrength = 25;
	name = "Hero";
}

//constructor that takes coord parameters
Hero::Hero(int row, int col, int strength, int numAttDie, int numDefDie,
	int bagCapacity) : Creature(bagCapacity) //: bag(bagCapacity)
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

//returns hero's strength to starting strength
void Hero::refresh()
{
	strength = startingStrength;
}



Hero::~Hero()
{
}
