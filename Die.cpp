/******************************************************************************
Class Die represents a single die that has a constructor defined number of 
sides and a roll function that returns a random number between 1 and the 
number of sides. It also has a function for returning the number of sides and
an isLoaded() function which returns false (to distinguish Die from the sub-
class LoadedDie).
******************************************************************************/



#include "Die.hpp"
#include "cs162_utilities.hpp"


//constructor that takes number of sides as a parameter
Die::Die(int numSidesIn)
{
	numSides = numSidesIn;
}

//destructor
Die::~Die()
{
}


//returns a random integer between 1 and number of sides
int Die::roll()
{
	return getRandIntInRange(1, numSides);
}

//returns the number of sides of the die
int Die::getNumSides()
{
	return numSides;
}

//returns false (because Die is not loaded)
bool Die::isLoaded()
{
	return false;
}


