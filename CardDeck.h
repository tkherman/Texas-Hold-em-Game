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
	char suit;
    int prime_value;
	void display() {
		
		string valName, suitName;
    	switch (suit)
    	{
			case 'd':
            	suitName = "Diamonds";
            	break;
        	case 'c':
            	suitName = "Clubs";
            	break;
        	case 'h':
            	suitName = "Hearts";
            	break;
        	case 's':
            	suitName = "Spades";
            	break;
    	}
		
		if(value == 1) {
			valName = "Ace";
		}
		else if(value == 11){
			valName = "Jack";
		}
		else if(value == 12){
			valName = "Queen";
		}
		else if(value == 13){
			valName = "King";
		}
		else {
			valName = to_string(value);
		}
		
		//acutal display
		cout << valName << " of " << suitName;
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
