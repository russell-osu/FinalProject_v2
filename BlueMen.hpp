// this is a header file for BlueMen.cpp

#ifndef MOON_BLUEMEN_HPP
#define MOON_BLUEMEN_HPP

#include "Creature.hpp"
class BlueMen :
	public Creature
{
public:
	BlueMen();
	virtual int defend(string attString);
	virtual void refresh();
	~BlueMen();
};

#endif
