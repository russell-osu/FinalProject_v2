// this is a header file for Game.cpp

#ifndef MOON_GAME_HPP
#define MOON_GAME_HPP
#include "Map.hpp"
#include "Space.hpp"
#include "defConst.hpp"
#include "Combat.hpp"


class Hero;

class Game
{
private:
	Map map;
	Space* spcArr[SPC_ROWS][SPC_COLS];
	Space* village;
	Space* currSpc;
	shared_ptr<Creature>hero;
	int movesRmn;
	int maxMoves;



public:
	Game(int maxMoves, shared_ptr<Creature>hero);
	void gameLogic();
	void engageCombat();
	bool chkWinCond();
	void updMovesRmn(int newMoves);
	void moveHero();
	void dispNewSpcMsg();
	void newSpcInit(int row, int col);
	void newSpcConnect(Space* tmpSpc);
	void setMovesRmn(int movesRmn);
	int getMovesRmn();
	void setMaxMoves(int maxMoves);
	int getMaxMoves();

	~Game();
};


#endif
