// this is a header file for Forest.cpp

#ifndef MOON_FOREST_HPP
#define MOON_FOREST_HPP
#include "Space.hpp"

class Forest :
	public Space
{
public:
	Forest();
	Forest(int row, int col);
	virtual int gatherRsc();
	virtual string describe();
	~Forest();
};

#endif
