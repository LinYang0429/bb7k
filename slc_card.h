#ifndef __SLC_CARD_H__
#define __SLC_CARD_H__

#include "card.h"

class SLC_Card : public Card{
	int arr[24];
	public:
		SLC_Card();
		virtual int getCard();
};


#endif
