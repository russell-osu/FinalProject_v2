// this is a header file for Game.cpp

#ifndef MOON_GAME_HPP
#define MOON_GAME_HPP
#include "Map.hpp"
#include "Space.hpp"
#include "defConst.hpp"


class Game
{
private:
	Map map;
	Space* spcArr[SPC_ROWS][SPC_COLS];
	Space* village;
	Space* currSpc;
	Creature* hero;
	int numMoves;
	int maxMoves;


public:
	Game(int maxMoves, Creature* hero);
	void gameLogic();
	void engageCombat();
	bool chkWinCond();
	void updNumMoves(int newMoves);
	void moveHero();
	void newSpcInit(int row, int col);
	void newSpcConnect(Space* tmpSpc);

	~Game();
};


#endif
