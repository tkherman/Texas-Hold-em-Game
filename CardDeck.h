// CardDeck.h

// This is the interface for the class that serves as a card deck in our simulated poker game
#include <vector>
using namespace std;

#ifndef CARDDECK_H
#define CARDDECK_H

struct Card{
	int value;
	char suit;
};

class CardDeck {
	public:
		CardDeck();
		~CardDeck();
		Card getCard();
		int getSize();
		void shuffle();
		void resetDeck();
	private:
		vector<Card> deck;
};


#endif