/******************************************************************************
Class: Resource
Name: Russell Moon
Date: 8/12/2017
Description: Resource is an abstract class (itself a subclass of the abstract
Item class). It has subclasses Stone, Wood and Ore.
******************************************************************************/

#include "Resource.hpp"
#include <iostream>


Resource::Resource()
{
	subclass = "resource";
}

//void Resource::use(std::shared_ptr<Creature> creat)
//{
//	std::cout << "This item can't be used." << std::endl << std::endl;
//}


Resource::~Resource()
{
}
