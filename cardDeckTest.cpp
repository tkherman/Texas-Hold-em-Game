// cardDeckTest.cpp

#include <iostream>
#include <vector>
#include "CardDeck.h"
using namespace std;

int main() {
	CardDeck deck;
	deck.shuffle();
	Card newcard = deck.getCard();
	newcard.display();
	cout << endl << deck.getSize() << endl;
	newcard = deck.getCard();
	newcard.display();
	cout << endl;
}
