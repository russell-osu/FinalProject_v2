// this is a header file for Consumable.cpp

#ifndef MOON_CONSUMABLE_HPP
#define MOON_CONSUMABLE_HPP
class Consumable
{
public:
	Consumable();
	virtual void use() = 0;
	virtual ~Consumable();
};

#endif
