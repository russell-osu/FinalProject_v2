// this is a header file for Vampire.cpp

#ifndef MOON_VAMPIRE_HPP
#define MOON_VAMPIRE_HPP

#include "Creature.hpp"
class Vampire :
	public Creature
{
public:
	Vampire();
	virtual int defend(string attString);
	virtual void refresh();

	~Vampire();
};


#endif

