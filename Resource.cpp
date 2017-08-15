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
