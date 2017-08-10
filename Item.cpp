#include "Item.hpp"



Item::Item()
{
}

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


Item::~Item()
{
}
