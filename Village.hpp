// this is a header file for Village.cpp

#ifndef MOON_VILLAGE_HPP
#define MOON_VILLAGE_HPP
#include "Space.hpp"
class Village :
	public Space
{
private:
	int stoneCnt;
	int woodCnt;
	int oreCnt;
public:
	Village();
	Village(int row, int col);
	virtual int gatherRsc();
	virtual string describe();
	bool buildShelter(shared_ptr<Creature>hero);
	void dispSheltRsc();
	//void cntSheltRsc();
	~Village();
};

#endif