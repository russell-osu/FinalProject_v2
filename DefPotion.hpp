// this is a header file for DefPotion.cpp

#ifndef MOON_DEFPOTION_HPP
#define MOON_DEFPOTION_HPP

#include "Consumable.hpp"
#include <memory>

class DefPotion :
	public Consumable
{
public:
	DefPotion();
	virtual void use(shared_ptr<Creature> creat);
	~DefPotion();
};

#endif
