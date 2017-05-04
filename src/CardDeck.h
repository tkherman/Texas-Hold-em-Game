// CardDeck.h

// This is the interface for the class that serves as a card deck in our simulated poker game
#include <vector>
#include <iostream>
#include <string>
using namespace std;

#ifndef CARDDECK_H
#define CARDDECK_H

struct Card{
	unsigned int value;
    char charVal;
	char suit;
    char suitIcon;
    int prime_value;
};

struct Player {
    Card hand[2];
    int playerNum;
    bool in_out;
	bool all_in;
    int best_rank;
    double cash_balance;
    bool computer;

    Player() {
        in_out = true;
		all_in = false;
        cash_balance = 60;
    }
};


class CardDeck {
	public:
		CardDeck();
		~CardDeck();
		Card getCard();
		int getSize();
		void shuffle();
		void remove(Card);
		void resetDeck();
	private:
		vector<Card> deck;
};


#endif
