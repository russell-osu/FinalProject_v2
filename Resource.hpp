// this is a header file for Resource.cpp

#ifndef MOON_RESOURCE_HPP
#define MOON_RESOURCE_HPP
#include "Item.hpp"

//Forward declaration of Creature
class Creature;

class Resource :
	public Item
{
public:
	Resource();
	//virtual void use(std::shared_ptr<Creature> creat);
	virtual ~Resource();
};

#endif
