/******************************************************************************
Class: Item
Name: Russell Moon
Date: 8/12/2017
Description: Item is an abstract base class which represents items that
Creatures can gather, hold and use. It has datamembers for describing an
items name, weight, and subclass/type.
******************************************************************************/

#include "Item.hpp"


Item::Item()
{
}

//used only for subclasses of Resource
void Item::setType(char type)
{
	this->type = type;
}

char Item::getType()
{
	return type;
}

void Item::setName(string name)
{
	this->name = name;
}

string Item::getName()
{
	return name;
}

void Item::setWeight(int weight)
{
	this->weight = weight;
}

int Item::getWeight()
{
	return weight;
}

void Item::setSubclass(string subclass)
{
	this->subclass = subclass;
}

string Item::getSubclass()
{
	return subclass;
}


Item::~Item()
{
}
