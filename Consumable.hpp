// this is a header file for Consumable.cpp

#ifndef MOON_CONSUMABLE_HPP
#define MOON_CONSUMABLE_HPP
#include "Item.hpp"
class Consumable :
	public Item
{
public:
	Consumable();
	virtual void use() = 0;
	virtual ~Consumable();
};

#endif
