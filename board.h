#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
//#include "player.h"
#include "square.h"

#include "block.h"
class Board{
//	protected:
		//Player * players[8]; // why store players?

		Block * Arts1;
		Block * Arts2;
		Block * Eng;
		Block * Health;
		Block * Env;
		Block * Sci1;
		Block * Sci2;
		Block * Math;
	public:

		Square * squares[40];
		Board();
		~Board();
		void init();
		void notifyMove(Player * player,int index);
		void notifyGoToTims(Player *p);
		void notifySLC(Player *p);

		// void notifyPlayerBankruptcy(Player * player);
		// void isWon();

};

#endif

