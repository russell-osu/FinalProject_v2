// this is a header file for AttPotion.cpp

#ifndef MOON_ATTPOTION_HPP
#define MOON_ATTPOTION_HPP
#include "Consumable.hpp"
#include <memory>
#include "Creature.hpp"

using std::shared_ptr;

class AttPotion :
	public Consumable
{
public:
	AttPotion();
	virtual void use(shared_ptr<Creature> creat);
	~AttPotion();
};

#endif
 