// this is a header file for Barbarian.cpp

#ifndef MOON_BARBARIAN_HPP
#define MOON_BARBARIAN_HPP


#include "Creature.hpp"
class Barbarian :
	public Creature
{
public:
	Barbarian();
	virtual void refresh();
	~Barbarian();
};



#endif
