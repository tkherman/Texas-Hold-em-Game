// CardDeck.cpp

// This is the implementation of the CardDeck class with basic functions that a
// normal deck of cards would have

#include <vector>
#include <random>
#include "CardDeck.h"
using namespace std;

// initialize a deck of cards
CardDeck::CardDeck() {
	Card tempC;
	char suits[] = {'d', 'c', 'h', 's'};
    char suitIcons[] = {'O', '+', '#', '@'};
    unsigned int prime[] = {0, 41, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

	for (int val = 1; val <= 13; val++) {
		for (int i = 0; i < 4; i++) {
			tempC.value = val;
			tempC.suit = suits[i];
            tempC.suitIcon = suitIcons[i];
            
            if (val == 1) 
                tempC.charVal = 'A';
            else if (val == 13)
                tempC.charVal = 'K';
            else if (val == 12)
                tempC.charVal = 'Q';
            else if (val == 11)
                tempC.charVal = 'J';
            else if (val == 10)
                tempC.charVal = 'T';
            else
                tempC.charVal = (char)val + '0';

            
            tempC.prime_value = prime[val];

			deck.push_back(tempC);
		}
	}

	shuffle();
}

CardDeck::~CardDeck() { }

// return a card while removing that card from deck
Card CardDeck::getCard() {
	Card returnCard = deck.back();
	deck.pop_back();
	return returnCard;
}

void CardDeck::remove(Card c) {
	for(int k=0; k<deck.size(); k++) {
		//check for equality; easier than overwriting equality operator
		if(deck[k].suit == c.suit && deck[k].value == c.value) {

			//using pop_back to avoid resizing entire list
			int backIndex = deck.size() - 1;
			//if at end, pop off the back
			if(k == backIndex)
				deck.pop_back();
			else { //swap and remove
				Card temp = deck[backIndex];
				deck[backIndex] = deck[k];
				deck[k] = temp;
				deck.pop_back();
			}
		}
	}
}

int CardDeck::getSize() {
	return deck.size();
}

// shuffle the deck
void CardDeck::shuffle() { // Fisher-Yates shuffle algorithm
	int n = getSize(), index;
	Card temp;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 200);

	while (n) {
		index = dist(mt) % n--; // random value 0 <= i < n
		temp = deck[n];
		deck[n] = deck[index];
		deck[index] = temp;
	}
}
