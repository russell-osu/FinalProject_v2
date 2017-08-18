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
	int stoneWin;
	int woodWin;
	int oreWin;



public:
	//parameters for amt of stone, wood and ore needed to win
	Game(int maxMoves, shared_ptr<Creature>hero, int stone, int wood, int ore);
	void gameLogic();
	void chkCreatBag(shared_ptr<Creature> currCreat);
	void updMovesRmn(int newMoves);
	void moveHero();
	void postMoveOp();
	void dispSpcMsg();
	void dispInstructions();
	void newSpcInit(int row, int col);
	void newSpcConnect(Space* tmpSpc);
	void setMovesRmn(int movesRmn);
	int getMovesRmn();
	void setMaxMoves(int maxMoves);
	int getMaxMoves();

	~Game();
};


#endif
