// this is a header file for Consumable.cpp

#ifndef MOON_CONSUMABLE_HPP
#define MOON_CONSUMABLE_HPP
#include "Item.hpp"
#include <memory>
#include "Creature.hpp"

////Forward declaration of Creature
//class Creature;

using std::shared_ptr;

class Consumable :
	public Item
{
public:
	Consumable();
	virtual void use(shared_ptr<Creature> creat) = 0;
	virtual ~Consumable();
};

#endif
