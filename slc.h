#ifndef _SLC_H_
#define _SLC_H_
#include <iostream>
#include "nonproperty.h"
#include "slc_card.h"
class Player;

class SLC: public Nonproperty{
	SLC_Card slc_card_fac;
	public:
		SLC(std::string name);
		void action(Player *player);
		int getCard() { return slc_card_fac.getCard(); }
};

#endif

