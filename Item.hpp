//this is a header file for Item.cpp

#ifndef MOON_ITEM_HPP
#define MOON_ITEM_HPP
#include <string>
#include <memory>


using std::string;

//Forward declaration of Creature
class Creature;

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
	//virtual void use(std::shared_ptr<Creature> creat) = 0;

	virtual ~Item();
};

#endif 