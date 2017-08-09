// this is a header file for Plains.cpp

#ifndef MOON_PLAINS_HPP
#define MOON_PLAINS_HPP
#include "Space.hpp"


class Plains :
	public Space
{
public:
	Plains();
	Plains(int row, int col);
	virtual int gatherRsc();
	virtual string describe();
	~Plains();
};

#endif
