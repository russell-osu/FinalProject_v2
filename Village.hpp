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
	int stoneWin;
	int woodWin;
	int oreWin;
public:
	Village();
	Village(int row, int col, int stone, int wood, int ore);
	virtual string describe();
	bool buildShelter(shared_ptr<Creature>hero);
	void dispSheltRsc();
	void setStoneCnt(int stone);
	int getStoneCnt();
	void setWoodCnt(int wood);
	int getWoodCnt();
	void setOreCnt(int ore);
	int getOreCnt();
	~Village();
};

#endif