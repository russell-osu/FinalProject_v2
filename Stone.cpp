/******************************************************************************
Class: Stone
Name: Russell Moon
Date: 8/12/2017
Description: Stone is a subclass of Resource (itself a subclass of Item). It is
collected by the player in order to build the shelter and satisfy the game's
win condition.
******************************************************************************/

#include "Stone.hpp"


Stone::Stone()
{
	type = 's';
	name = "stone";
	weight = 4;
}




Stone::~Stone()
{
}
