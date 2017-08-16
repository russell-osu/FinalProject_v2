// this is a header file for StrPotion.cpp

#ifndef MOON_STRPOTION_HPP
#define MOON_STRPOTION_HPP

#include "Consumable.hpp"
#include <memory>


class StrPotion :
	public Consumable
{
public:
	StrPotion();
	virtual void use(shared_ptr<Creature> creat);
	~StrPotion();
};

#endif