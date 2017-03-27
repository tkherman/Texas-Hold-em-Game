// Round.cpp
// This is the implementation of the Round class

#include <iostream>
#include <vector>
#include "Round.h"
#include "CardDeck.h"
using namespace std;


Round::Round(int n) {
	numPlayers = n;

	/* first step: deal cards to each player, determine who's in and out*/
	deal(numPlayers);
	for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
		if (it->in_out) {
			print_players(it->playerNum);
			player_action(it->playerNum);
		}
	}


	/* if there are more than 1 player, do initial flop and determines who's still in */
	if (playerVec.size() > 1) {
		for (int i = 0; i < 3; i++) {
			flop();
		}
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				player_action(it->playerNum);
			}
		}
	}
	

	/* if there are more than 1 player, do another flop and determines who's still in */
	if (playerVec.size() > 1) {
		flop();
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				player_action(it->playerNum);
			}
		}
	}
	


	/* if there are more than 1 player, do the final flop, determines who's still in */
	if (playerVec.size() > 1) {
		flop();
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				player_action(it->playerNum);
			}
		}
	}
	


	/* if more than 1 player left, compare hands */
	//if (playerVec.size() > 1) winner = determine_winner;

}

Round::~Round() { };

void Round::deal(int numPlayers) {
	// create temp_player, assign 2 cards and add temp_player to vector
	for (int i = 0; i < numPlayers; i++) {
		Player temp_player;
		temp_player.playerNum = i;
		temp_player.hand[0] = deck.getCard();
		temp_player.hand[1] = deck.getCard();
		temp_player.in_out = true;
		playerVec.push_back(temp_player);
	}
}

void Round::flop() {
	Card temp_card;
	temp_card = deck.getCard();
	communityVec.push_back(temp_card);
}

// This function determines if the player stays or not
// If player folds, remove from vector
// If player stays, do nothing
void Round::player_action(int pNum) {
	char input;
	cout << "fold or stay in? f for fold, s for stay: ";
	cin >> input;
	if (input == 'f') {
		playerVec[pNum].in_out = false;
	}
}

// This function prints out the community cards
void Round::print_community() {
	cout << "-------Community Cards---------" << endl;
	for (auto it = communityVec.begin(); it != communityVec.end(); it++) {
		it->display();
		cout << " || ";
	}
	cout << endl << endl << endl;
}

void Round::print_players(int playerN) {
	cout << "player" << playerN << ":" << endl;
	playerVec[playerN].hand[0].display();
	cout << endl;
	playerVec[playerN].hand[1].display();
	cout << endl;
}
