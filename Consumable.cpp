/******************************************************************************
Class: Consumable
Name: Russell Moon
Date: 8/12/2017
Description: This is an abstract subclass of Item, which models consumable
items that Creatures can use. It has subclasses AttPotion, DefPotion and
StrPotion.
******************************************************************************/

#include "Consumable.hpp"


Consumable::Consumable()
{
	subclass = "consumable";
}



Consumable::~Consumable()
{
}
