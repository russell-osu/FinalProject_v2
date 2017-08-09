// this is a header file for Hills.cpp

#ifndef MOON_HILLS_HPP
#define MOON_HILLS_HPP
#include "Space.hpp"
class Hills :
	public Space
{
public:
	Hills();
	Hills(int row, int col);
	virtual int gatherRsc();
	virtual string describe();
	~Hills();
};

#endif