#include <iostream>
#include "nh.h"
#include "player.h"
#include "nonproperty.h"
#include "nh_card.h"
using namespace std;

NH:: NH(string name): Nonproperty(name){}

void NH:: action(Player *player){    // action of player after landing on NH

	int card = nh_card_fac.getCard();

	cout << "You get a card from Needles Hall: " << card << endl;

	if(card == 0) {
		player->setMoney(player->getMoney() -200);
		player->setWorth(player->getWorth() -200);
		cout << "You lost $200" << endl;
	} else if (card == 1) {
		player->setMoney(player->getMoney() - 100);
		player->setWorth(player->getWorth() -100);
		cout << "You lost $100" << endl;
	} else if (card == 2) {
		player->setMoney(player->getMoney() -50);
		player->setWorth(player->getWorth() -50);
		cout << "You lost $50" << endl;
	} else if (card == 3) {
		player->setMoney(player->getMoney() + 25);
		player->setWorth(player->getWorth() + 25);
		cout << "You got $25" << endl;
	} else if (card == 4) {
		player->setMoney(player->getMoney() + 50);
		player->setWorth(player->getWorth() + 50);
		cout << "You got $50" << endl;
	} else if (card == 5) {
		player->setMoney(player->getMoney() + 100);
						player->setWorth(player->getWorth() + 100);
						cout << "You got $100" << endl;
	} else {
		player->setMoney(player->getMoney() + 200);
						player->setWorth(player->getWorth() + 200);
						cout << "You got $200" << endl;
	}
	return;
}


