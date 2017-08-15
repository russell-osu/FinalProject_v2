// this is a header file for Wood.cpp

#ifndef MOON_WOOD_HPP
#define MOON_WOOD_HPP
#include "Item.hpp"
#include "Resource.hpp"

class Wood :
	public Resource
{
public:
	Wood();
	virtual void use();
	~Wood();
};

#endif