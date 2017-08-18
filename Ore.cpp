/******************************************************************************
Class: Ore
Name: Russell Moon
Date: 8/12/2017
Description: Ore is a subclass of Resource (itself a subclass of Item). It is
collected by the player in order to build the shelter and satisfy the game's
win condition.
******************************************************************************/

#include "Ore.hpp"



Ore::Ore()
{

	type = 'o';
	name = "ore";
	weight = 2;
	
}



Ore::~Ore()
{
}
