/******************************************************************************
Class: Wood
Name: Russell Moon
Date: 8/12/2017
Description: Wood is a subclass of Resource (itself a subclass of Item). It is
collected by the player in order to build the shelter and satisfy the game's
win condition.
******************************************************************************/

#include "Wood.hpp"



Wood::Wood()
{
	type = 'w';
	name = "wood";
	weight = 1;
}




Wood::~Wood()
{
}
