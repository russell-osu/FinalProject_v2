// this is a header file for Map.cpp

#ifndef MOON_MAP_HPP
#define MOON_MAP_HPP
class Map
{
private:
	char mapArr[29][37];
public:
	Map();
	void updateMapSpc(int row, int col, char spcTyp);
	void updateMapHero(int row, int col, int prvRow=0, int prvCol=0);
	void dispMap();
	~Map();
};

#endif
