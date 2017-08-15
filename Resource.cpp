#include "Resource.hpp"
#include <iostream>


Resource::Resource()
{
	subclass = "resource";
}

void Resource::use()
{
	std::cout << "This item can't be used." << std::endl << std::endl;
}


Resource::~Resource()
{
}
