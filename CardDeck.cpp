// CardDeck.cpp

// This is the implementation of the CardDeck class with basic functions that a
// normal deck of cards would have

#include <vector>
#include <stdlib.h>
#include "CardDeck.h"
using namespace std;

// initialize an unshuffled deck of cards
CardDeck::CardDeck() {
	Card tempC;
	char suits[] = {'d', 'c', 'h', 's'};

	for (int val = 1; val <= 13; val++) {
		for (const auto &suit: suits) {
			tempC.value = val;
			tempC.suit = suit;

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

int CardDeck::getSize() {
	return deck.size();
}

// shuffle the deck
void CardDeck::shuffle() { // Fisher-Yates shuffle algorithm
	int n = getSize(), index;
	Card temp;

	while (n) {
		srand(time(NULL)); 
		index = rand() % n--; // random value 0 <= i < n
		temp = deck[n];
		deck[n] = deck[index];
		deck[index] = temp;
	}
}
