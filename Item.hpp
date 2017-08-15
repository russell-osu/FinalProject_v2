//this is a header file for Item.cpp

#ifndef MOON_ITEM_HPP
#define MOON_ITEM_HPP
#include <string>

using std::string;

class Item
{
protected:
	string subclass;
	char type;
	string name;
	int weight;

public:
	Item();
	void setType(char type);
	char getType();
	void setName(string name);
	string getName();
	void setWeight(int weight);
	int getWeight();
	void setSubclass(string);
	string getSubclass();
	virtual void use() = 0;

	virtual ~Item();
};

#endif 