// this is a header file for Medusa.cpp

#ifndef MOON_MEDUSA_HPP
#define MOON_MEDUSA_HPP

#include "Creature.hpp"
class Medusa :
	public Creature
{
public:
	Medusa();
	virtual string attack();
	virtual void refresh();
	~Medusa();
};

#endif
