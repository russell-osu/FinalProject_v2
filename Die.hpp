#ifndef MOON_DIE_HPP
#define MOON_DIE_HPP

class Die
{
protected:
	int numSides;

public:
	int roll();
	bool isLoaded();
	int getNumSides();
	Die(int numSidesIn);
	~Die();
};

#endif

