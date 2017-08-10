//this is a header file for Item.cpp

#ifndef MOON_ITEM_HPP
#define MOON_ITEM_HPP
#include <string>

using std::string;

class Item
{
protected:
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
	virtual ~Item();
};

#endif 