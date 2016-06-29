#include "slc_card.h"
#include <assert.h>
#include <cstdlib>

#include <iostream>
using namespace std;

SLC_Card::SLC_Card() {
	int pos = 0;
	for (int i=0; i<3; i++) {
		arr[pos++] = 0;
	}

	for (int i=0; i<4; i++) {
		arr[pos++] = 1;
	}
	for (int i=0; i<4; i++) {
		arr[pos++] = 2;
	}
	for (int i=0; i<3; i++) {
		arr[pos++] = 3;
	}
	for (int i=0; i<4; i++) {
		arr[pos++] = 4;
	}
	for (int i=0; i<4; i++) {
		arr[pos++] = 5;
	}
	arr[pos++] = 6;
	arr[pos++] = 7;
	assert(pos == 24);
}

int SLC_Card::getCard() {
	int res = rand() % 24;
cout << "getCard : index = " << res << endl;
	return (int)arr[res];
}
