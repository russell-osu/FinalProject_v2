// this is a header file for Bag.cpp

#ifndef MOON_BAG_HPP
#define MOON_BAG_HPP
#include <vector>
#include <memory>
#include "Item.hpp"

using std::vector;
using std::shared_ptr;

class Bag
{
private:
	int capacity;
	int currWght;
	vector<shared_ptr<Item>> bagVect;

public:
	Bag();
	Bag(int capacity);

	bool addItm(shared_ptr<Item> item);
	Item* rmvItm(int itemNum);
	void examItm();
	void dispContents();
	void setCapacity(int capacity);
	int getCapacity();
	void setCurrWght(int currWght);
	int getCurrWght();
	vector<shared_ptr<Item>> getBagVect();

	~Bag();
};

#endif