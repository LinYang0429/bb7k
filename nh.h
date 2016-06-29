#ifndef _NH_H_
#define _NH_H_
#include <iostream>
#include "nonproperty.h"

#include "nh_card.h"

class NH: public Nonproperty{

	NH_Card nh_card_fac;
	public:
		NH(std::string name);
		void action(Player *player);
};

#endif

