#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>

#include "controller.h"
#include "academic.h"
#include "block.h"
#include "gym.h"
#include "residence.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "display.h"
#include "rurc.h"
using namespace std;

Controller::Controller() {
	for (int i = 0; i < 8; ++i) {
		players[i] = NULL;
		playername[i] = "";
	}
	r = new Rurc("rurc");
	current = 0;
	numPlayer = 0;
	board = new Board();
	display = new Display();
	checkWin = 0;
}

void Controller::roll(Player *p) {
	if ((p->alreadyRoll == true) && (p->numDoubleroll == 0 || p->numDoubleroll == 3)) {     // if this is not the first time to roll and did not get double for last run
		cout << "You cannot roll for second time" << endl;
		//p->alreadyRoll = false;
		return;
	} 

	//if (p->numDoubleroll == 3) p->numDoubleroll = 0;

	int d1 = rand() % 6 + 1;
	int d2 = rand() % 6 + 1;
	cout << "You get " << d1 << " and " << d2 << endl;

	if (p->alreadyRoll == false) p->alreadyRoll = true;
	
//	p->numRoll++;
	if (d1 == d2) {         // record the # of double roll
		++p->numDoubleroll;
	} else {
		p->numDoubleroll = 0;
	}

	if (p->numDoubleroll == 3) {      // if player rolls double 3 times consecutively
		board->notifyGoToTims(p);
	}
	
	//when the player is in Dc Tims	line
	if(p->getIndex() == 10){
		p->numRoll++;
               	if (p->getNumRurc() != 0){
			cout << "Would you like to use a Roll Up the Rim cup card? " << endl;
                        cout << "Please enter y(as yes) or n(as no)." << endl;
                        string s;
                        cin >> s;
                        if(s == "y"){
                                r->action(p);
                                cout << "You counld leave DC Tims line." << endl;
                                return;
                        }
		}else if(p->numRoll == 3 || p->numDoubleroll != 0){
                        p->setMoney(p->getMoney() - 50);
                        p->setWorth(p->getWorth() - 50);
                        cout << "Congratulations! You can leave DC Tims line! And you pay $50 for the cap." << endl;
			return;
                }else{
                        cout << "Sorry, you can't leave DC Tims line." << endl;
			return;
                }
	}
	//	Player *currentp = players[current];
	int newp = p->getIndex() + d1 + d2;

	if(newp == 10){
		p->numRoll = 0;
	}
//	currentp->setIndex(newp);

	cout << "Now your new position is " << board->squares[newp]->getName() << endl;
	board->notifyMove(p, newp);

//	(board->squares[newp])->action(p);	

	if ((p->numDoubleroll == 1) || (p->numDoubleroll == 2)) {     // rolled double once or twice
		cout << "You should roll again" << endl;
        }

	if(newp == 30){
		board->notifyGoToTims(p);
	}
	
	if((newp != 0)&&(newp != 2)&&(newp != 4)&&(newp != 7)&&(newp != 10)&&(newp != 17)&&(newp != 20)&&(newp != 22)&&(newp != 30)&&(newp != 33)&&(newp != 36)&&(newp != 38)){
		display->notifyPurchase(board, newp);
	}
	if ((newp == 17)||(newp == 33)||(newp == 2)) {  // when palyers land on SLC
		board->notifySLC(p);
	}
}


void Controller::roll_test(Player *p) {
	if ((p->alreadyRoll == true) && (p->numDoubleroll == 0)) {     // if this is not the first time to roll and did not get double for last run
		cout << "You cannot roll for second time" << endl;
		p->alreadyRoll = false;
		return;
	} 

	if (p->numDoubleroll == 3) p->numDoubleroll = 0;

	//int d1 = rand() % 6 + 1;
	//int d2 = rand() % 6 + 1;
	int d1, d2;
	cin >> d1;
	cin >> d2;
	cout << "You get " << d1 << " and " << d2 << endl;

	if (p->alreadyRoll == false) p->alreadyRoll = true;
	
//	p->numRoll++;
	if (d1 == d2) {         // record the # of double roll
		++p->numDoubleroll;
	} else {
		p->numDoubleroll = 0;
	}

	if (p->numDoubleroll == 3) {      // if player rolls double 3 times consecutively
		board->notifyGoToTims(p);
	}
	
	//when the player is in Dc Tims	line
	if(p->getIndex() == 10){
		p->numRoll++;
               	if (p->getNumRurc() != 0){
			cout << "Would you like to use a Roll Up the Rim cup card? " << endl;
                        cout << "Please enter y(as yes) or n(as no)." << endl;
                        string s;
                        cin >> s;
                        if(s == "y"){
                                r->action(p);
                                cout << "You counld leave DC Tims line." << endl;
                                return;
                        }
		}else if(p->numRoll == 3 || p->numDoubleroll != 0){
                        p->setMoney(p->getMoney() - 50);
                        p->setWorth(p->getWorth() - 50);
                        cout << "Congratulations! You can leave DC Tims line! And you pay $50 for the cap." << endl;
			return;
                }else{
                        cout << "Sorry, you can't leave DC Tims line." << endl;
			return;
                }
	}
	//	Player *currentp = players[current];
	int newp = p->getIndex() + d1 + d2;

	if(newp == 10){
		p->numRoll = 0;
	}
//	currentp->setIndex(newp);

	cout << "Now your new position is " << board->squares[newp]->getName() << endl;
	board->notifyMove(p, newp);

//	(board->squares[newp])->action(p);	

	if ((p->numDoubleroll == 1) || (p->numDoubleroll == 2)) {     // rolled double once or twice
		cout << "You should roll again" << endl;
        }

	if(newp == 30){
		board->notifyGoToTims(p);
	}
	
	if((newp != 0)&&(newp != 2)&&(newp != 4)&&(newp != 7)&&(newp != 10)&&(newp != 17)&&(newp != 20)&&(newp != 22)&&(newp != 30)&&(newp != 33)&&(newp != 36)&&(newp != 38)){
		display->notifyPurchase(board, newp);
	}

	if ((newp == 17)||(newp == 33)||(newp == 2)) {  // when palyers land on SLC
		board->notifySLC(p);
	}
}

void Controller::trade(Player *p) {
	string name;
	string give;
	string receive;
	int givem;
	int receivem;

	cin >> name >> give >> receive;
//	istringstream sso(give);  // check give a building or money
//	if (!(sso >> givem)) givem = -1;
//
//	istringstream sst(receive); // check receive a buildingor money
//	if (!(sst >> receivem)) receivem = -1;

	if (give[0] >= '0' && give[0] <= '9') {
		givem = atoi(give.c_str());
	} else {
		givem = -1;
	}

	if (receive[0] >= '0' && receive[0] <= '9') {
		receivem = atoi(receive.c_str());
	} else {
		receivem = -1;
	}
	if (givem >= 0 && receivem >= 0) {
		cout << "Invalid trade(cannot trade money with money). Please try again" << endl;
		return;
	}

	Player *receiver = NULL;
	for (int i = 0; i < numPlayer; ++i) {
		if (players[i]->getName() == name) {
			receiver = players[i];
			break;
		}
	}
	
	cout << "accept/reject?" << endl;
	string resp;
	cin >> resp;
	if (resp == "reject") {
		return;
	}

	int step = 0;     // record the step of trading finished

	if (givem < 0) {
		if (receivem < 0) {
			for (int i = 0; i < p->numAcademic; ++i) {
				if ((p->getAcademic()[i])->getName() == give) {
					receiver->setAcademic(p->getAcademic()[i]);
					p->rmAcademic(p->getAcademic()[i]);
					++step;
				}
				if ((receiver->getAcademic()[i])->getName() == receive) {
					p->setAcademic(receiver->getAcademic()[i]);
					receiver->rmAcademic(p->getAcademic()[i]);
					++step;
				}
				if (step == 2) return;
			}

			for (int i = 0; i < p->numResidence; ++i) {
				if ((p->getResidence()[i])->getName() == give) {
					receiver->setResidence(p->getResidence()[i]);
					p->rmResidence(p->getResidence()[i]);
					++step;
				}
				if ((receiver->getResidence()[i])->getName() == receive) {
					p->setResidence(receiver->getResidence()[i]);
					receiver->rmResidence(p->getResidence()[i]);
					++step;
				}
				if (step == 2) return;
			}

			for (int i = 0; i < p->numGym; ++i) {
				if ((p->getGym()[i])->getName() == give) {
					receiver->setGym(p->getGym()[i]);
					p->rmGym(p->getGym()[i]);
					++step;
				}
				if ((receiver->getGym()[i])->getName() == receive) {
					p->setGym(receiver->getGym()[i]);
					receiver->rmGym(p->getGym()[i]);
					++step;
				}
				if (step == 2) return;
			}
		}else {
			for (int i = 0; i < p->numAcademic; ++i) {
				if ((p->getAcademic()[i])->getName() == give) {
					Academic *temp = p->getAcademic()[i];
					for (int j = 0; j < 3; ++j) {
						if (temp->block->blo[j] == NULL) break;
						if (temp->block->blo[j]->getImproveLevel() != 0) {
							cout << "Invalid trading. Please try again" << endl;
							return;
						}
					}

					receiver->setAcademic(p->getAcademic()[i]);
					p->rmAcademic(p->getAcademic()[i]);
				}
			}
			for (int i = 0; i < p->numResidence; ++i) {
				if ((p->getResidence()[i])->getName() == give) {
					receiver->setResidence(p->getResidence()[i]);
					p->rmResidence(p->getResidence()[i]);
					++step;
				}
			}
			for (int i = 0; i < p->numGym; ++i) {
				if ((p->getGym()[i])->getName() == give) {
					receiver->setGym(p->getGym()[i]);
					p->rmGym(p->getGym()[i]);
					++step;
				}
			}
			p->setMoney(p->getMoney() + receivem);
			receiver->setMoney(p->getMoney() - receivem);
		}
	} else {
		for (int i = 0; i < receiver->numAcademic; ++i) {
			if ((receiver->getAcademic()[i])->getName() == receive) {
				Academic *a = receiver->getAcademic()[i];
				p->setAcademic(a);
				receiver->rmAcademic(a);
				display->notifyPurchase(board, receiver->getAcademic()[i]->getIndex());
			}
		}
		for (int i = 0; i < receiver->numResidence; ++i) {
			if ((receiver->getResidence()[i])->getName() == receive) {
				Residence *r = receiver->getResidence()[i];
				p->setResidence(r);
				receiver->rmResidence(r);
				display->notifyPurchase(board, r->getIndex());
			}
		}
		for (int i = 0; i < p->numGym; ++i) {
			if ((receiver->getGym()[i])->getName() == give) {
				Gym *gym = receiver->getGym()[i];
				p->setGym(gym);
				receiver->rmGym(gym);
				display->notifyPurchase(board, gym->getIndex());
			}
		}
		p->setMoney(p->getMoney() - givem);
		receiver->setMoney(p->getMoney() + givem);

	}

}



void Controller::improve(Player *p) {      // 
	string bu;
	cin >> bu;
	Academic *property = NULL;

	for (int i = 0; i < p->numAcademic; ++i) {
		if ((p->getAcademic()[i])->getName() == bu) {
			property = p->getAcademic()[i];
		}
	}

	if (property == NULL) {
		cout << "You don't own the building so you cannot improve it. Please try again" << endl;
		return;
	}
	int ind;
	for (int i = 0; i < 40; ++i) {
		if( board->squares[i] == property){
			ind = i;
			break;
		}
	}

	string in;
	cin >> in;

//	Player *currentp = players[current];

	if (in == "buy") {	
		if (!property->block->isMonopoly) {
			cout << "Cannot improve " << property->getName()<< " because " << property->block->getName() << " is not monopoly" << endl; 
			return;
		}
		
		if (property->getImproveLevel() >= 5) {
			cout << "Cannot improve " << property->getName()<< " because it is at the highest level" << endl; 
			return;
		}
		p->setMoney(p->getMoney() - (property->block)->getImproveCost());
		property->setImproveLevel(property->getImproveLevel() + 1);
		cout << "You have improved your building to level " << property->getImproveLevel() << endl;
		this->display->notifyImplove(property, ind);
	} else if (in == "sell") {
		if (property->getImproveLevel() <= 0) {
			cout << "Cannot sell improvement " << property->getName()<< " because it is at level 0" << endl; 
			return;
		}
		p->setMoney(p->getMoney() - (property->block)->getImproveCost());		
		display->notifyImploveSell(property, ind);
		property->setImproveLevel(property->getImproveLevel() - 1);
		cout << "You have cut your improvement to level " << property->getImproveLevel() << endl;
	} else { 
		cout << "Invalid command. Please try again" << endl;
		return;
	}
}

void Controller::mortage(Player *p) {
	string bu;
	cin >> bu;
	Building *property = NULL;

	for (int i = 0; i < 22; ++i) {
		if ((p->getAcademic()[i])->getName() == bu) {
			property = p->getAcademic()[i];       // is it ok to use assignment like this?  ?  ?
		}                       
	}                       

	/*   if (property != NULL) {
	     if (isMortaged) {
	     cout << "Invalid command. Please try again" << endl;
	     return;
	     }

	     p->setMoney(p->getMoney() + 0.5 * property->getPurchaseFee());
	     isMortaged = true;
	     return;
	     }  */

	for (int i = 0; i < 4; ++i) {
		if ((p->getResidence()[i])->getName() == bu) {
			property = p->getResidence()[i];
		}
	}

	for (int i = 0; i < 2; ++i) {
		if((p->getGym()[i])->getName() == bu) {
			property = p->getGym()[i];
		}
	}

	if (property == NULL) {
		cout << "You don't own the building. Please try again" << endl;
		return;
	} else if (property->getImproveLevel() != 0) {
		cout << "You cannot mortage the building because you need to sell your improvement first" << endl;
	} 

	else {
		if (property->isMortaged) {
			cout << "Invalid input. Please try again" << endl;
			return;
		}
		p->setMoney(p->getMoney() + 0.5 * property->getPurchaseFee());
		property->isMortaged = true;
		return;
	}

}

void Controller::unmortage(Player *p) {
	string bu;
	cin >> bu;
	Building *property = NULL;
	for (int i = 0; i < 22; ++i) {
		if ((p->getAcademic()[i])->getName() == bu) {
			property = p->getAcademic()[i];       // is it ok to use assignment like this?  ?  ?
		}
	}

	for (int i = 0; i < 4; ++i) {
		if((p->getResidence()[i])->getName() == bu) {
			property = p->getResidence()[i];
		}
	}

	for (int i = 0; i < 2; ++i) {
		if((p->getGym()[i])->getName() == bu) {
			property = p->getGym()[i];
		}
	}

	if (property == NULL) {
		cout << "You don't own the building. Please try again" << endl;
		return;
	}

	if (p->getMoney() < 0.6 * property->getPurchaseFee()) {
		cout << "You cannot unmortage the building because you don't have enough money" << endl;
		return;
	}

	if (property->isMortaged) {
		p->setMoney(p->getMoney() - 0.6 * property->getPurchaseFee());
		property->isMortaged = false;
		return;
	}
}

void Controller::bankrupt(Player *p) {
	--numPlayer;
	if (numPlayer == 1) {
		checkWin = true;
		return;
	}

	if (numPlayer != current) {
		for (int i = current; i < numPlayer; ++i) {
			players[i] = players[i+1];
		}
	}

	Building *temp = dynamic_cast<Building *>(board->squares[p->getIndex()]);
	Player *receiver = temp->owner;   // reciever is the owner of the square where p is                       ??? why owner public not work
	for (int i = 0; i < p->numAcademic; ++i) {
		receiver->setAcademic(p->getAcademic()[i]);
		//++receiver->numAcademic;
	}

	for (int i = 0; i < p->numResidence; ++i) {
		receiver->setResidence(p->getResidence()[i]);
		++receiver->numResidence;
	}

	for (int i = 0; i < p->numGym; ++i) {
		receiver->setGym(p->getGym()[i]);
		++receiver->numGym;
	}

	receiver->setMoney(receiver->getMoney() + p->getMoney());
	receiver->setWorth(receiver->getWorth() + p->getWorth());

	display->notifyBankrupcy(board, p);
	delete p;
}

void Controller::assets(Player *p) {
	cout << "You have $" << p->getMoney() << endl; 
	cout << "You own ";

	bool ownBuilding = false;

	for (int i = 0; i < p->numAcademic; ++i) {
		if (p->getAcademic()[i] != NULL) {
			cout << (p->getAcademic()[i])->getName() << endl;
			ownBuilding = true;
		}
	}

	for (int i = 0; i < p->numResidence; ++i) {
		if (p->getResidence()[i] != NULL) {
			cout << (p->getResidence()[i])->getName() << endl;
			ownBuilding = true;
		}
	}

	for (int i = 0; i < p->numGym; ++i) {
		if (p->getGym()[i] != NULL) {
			cout << (p->getGym()[i])->getName() << endl;
			ownBuilding = true;
		}
	}

	if (!ownBuilding) {
		cout << "no building" << endl;
	}
}

/*bool Controller::checkWin() const{
	return numPlayer == 1;
}*/

void Controller::save() {
	string filename;
	cin >> filename;

	fstream fs(filename.c_str(), fstream::out);
	
	fs << numPlayer << endl;	
	for (int i=0; i<numPlayer; i++) {
		Player *p = players[i];
		fs << playername[i] << " " << p->getName()[0] << " " << p->getNumRurc() << " " << p->getMoney() << " " << p->getIndex();
		int is_line = (p->getIndex() == 10)?1:0;
		if (is_line == 1) {
			fs << " " << is_line << " " << p->numRoll;
		}
		fs << endl;
	}
	for(int i=0; i<40; i++){
		if((i == 1)||(i == 3)||(i == 6)||(i == 8)||(i == 9)||(i == 11)||(i == 13)||(i == 14)||(i == 16)||(i == 18)||(i == 19)||(i == 21)||(i == 23)||(i == 24)||(i == 26)||(i == 27)||(i == 29)||(i == 31)||(i == 32)||(i == 34)||(i == 37)||(i == 39)){
			Building *temp = dynamic_cast<Building*>(board->squares[i]);
			Academic *tem = dynamic_cast<Academic *>(board->squares[i]);
			Player *o = temp->getOwner();
			string own;
			if (o == NULL) own = "NONE";
			else own = o->getName(); 
			fs << temp->getName() << " " << own << " " << tem->getImproveLevel() << endl;
		}
	}

	fs.close();
}

//void Controller::load() {
//	
//}

void Controller::play() {
	srand(time(NULL));  // why?
	// map<string, >
	int nump;
	display->print();
	cout << "Please enter the number of players: " << endl;
	cin >> nump;
	numPlayer = nump;
	cout << "Please enter the name of players and then the char chosen from the list: G, B, D, P, S, $, L, T" << endl;

	for (int i = 0; i < numPlayer; ++i) {
		string name;
		string charac;
		cin >> name >> charac;
		playername[i] = name;
		players[i] = new Player(charac, 1500, 1500, 0, 0, 0, 0, 0, 0, 0);
		//cin.clear();
	}

	cin.clear();
	cin.ignore();

	cout << "Player: " << playername[current] << endl;

	Player *currentp;
	string cmd;
	
	while (true) {          // break loop after checking a win
		cin >> cmd;
		if (cin.fail()) break;		

		currentp = players[current];
//		cout << "Player: " << playername[current] << endl;
		if (cmd == "roll") {

			/* 	if (players[current]->haveRolled == true) { 
				cout << "You cannot roll again" << endl;
				} else { */
			roll(currentp);    // how to judge if the player has already rolled?
		} else if (cmd == "roll_test") {
			roll_test(currentp);
		} else if (cmd == "next") {
		/*	if (players[current+1] == NULL) {
				current = 0;
			} else {
				++current;
			}     */

			currentp->numDoubleroll = 0;
			currentp->alreadyRoll = false;
				
			current = (current + 1) % numPlayer;

			cout << "Player: " << playername[current] << endl;
			continue;
		} else if (cmd == "trade") {
			trade(currentp);
		} else if (cmd == "improve") {
			improve(currentp);	
		} else if (cmd == "mortage") {
			mortage(currentp);
		} else if (cmd == "unmortage") {
			unmortage(currentp);
		} else if (cmd == "bankrupt") {
			bankrupt(currentp);
			if (checkWin) { 
				cout << players[0]->getName() << " won" << endl
					<< "Game over" << endl;
				break;	
			    }
		    }
		else if (cmd == "assets") {
			assets(currentp);
		} else if (cmd == "save") {
			save();
		cout << "saved...exiting game" << endl;
			break;
		} else {
			cout << "Invalid command. Please try again" << endl;
		}

	display->print();

	}
		//   ?  ?  ?  delete?
}

Controller::~Controller() {
	delete r;
	delete board;
	delete display;
}

