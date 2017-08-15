// this is a header file for Resource.cpp

#ifndef MOON_RESOURCE_HPP
#define MOON_RESOURCE_HPP
#include "Item.hpp"
class Resource :
	public Item
{
public:
	Resource();
	virtual void use();
	virtual ~Resource();
};

#endif
