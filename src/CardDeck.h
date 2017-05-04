// CardDeck.h

// This is the interface for the class that serves as a card deck in our simulated poker game
#include <vector>
#include <iostream>
#include <string>
using namespace std;

#ifndef CARDDECK_H
#define CARDDECK_H

/* structure that represents a card */
struct Card{
	unsigned int value;
    char charVal;
	char suit;
    char suitIcon;
    int prime_value;
};

/* holds data for a player in the game */
struct Player {
    Card hand[2]; //the hand
    int playerNum; //which player it is
    bool in_out; //whether the player is still in a round
	bool all_in; //if a player has gone all in
    int best_rank; //rank of the player's best overall hand
    double cash_balance; 
    bool computer; //whether or not player is a computer player

    Player() {
        in_out = true;
		all_in = false;
        cash_balance = 250;
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
