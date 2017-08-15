// this is a header file for HarryPotter.cpp

#ifndef MOON_HARRYPOTTER_HPP
#define MOON_HARRYPOTTER_HPP


#include "Creature.hpp"
class HarryPotter :
	public Creature
{
private:
	int lives;
public:
	HarryPotter();
	virtual int defend(string attString);
	virtual void refresh();
	void setLives(int lives);
	int getLives();
	~HarryPotter();
};

#endif
