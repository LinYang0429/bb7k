#include "nh_card.h"
#include <assert.h>
#include <cstdlib>
#include <assert.h>
#include <cstdlib>
#include <iostream>
using namespace std;

NH_Card::NH_Card() {
        int pos = 0;

        arr[pos++] = 0;

        for (int i=0; i<2; i++) {
                arr[pos++] = 1;
        }
        for (int i=0; i<3; i++) {
                arr[pos++] = 2;
        }
        for (int i=0; i<6; i++) {
                arr[pos++] = 3;
        }
        for (int i=0; i<3; i++) {
                arr[pos++] = 4;
        }
        for (int i=0; i<2; i++) {
                arr[pos++] = 5;
        }

	arr[pos++] = 6;
        assert(pos == 18);
}

int NH_Card::getCard() {
        int res = rand() % 18;
cout << "getCard : index = " << res << endl;
        return (int)arr[res];
}





