// cardDeckTest.cpp

#include <iostream>
#include <vector>
#include "CardDeck.h"
using namespace std;


int main() {
	CardDeck deck;
	deck.shuffle();
	Card newcard = deck.getCard();
	cout << newcard.value << "," << newcard.suit << endl;
	cout << deck.getSize() << endl;
	newcard = deck.getCard();
	cout << newcard.value << "," << newcard.suit << endl;
}