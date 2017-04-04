// Round.h
// This is the class interface for Round class which allow the playing of a round
#include <vector>
#include <iostream>
#include "CardDeck.h"
#include "handTable.h"
using namespace std;

#ifndef ROUND_H
#define ROUND_H

struct Player {
    Card hand[2];
    int playerNum;
    bool in_out;
    int max_prime;
};

class Round {
	public:
		Round(int, unordered_map<int, int>&, unordered_map<int, int>&); // initialize players
		~Round();
		void deal(int); // for each player, deal 2 cards
		void flop();
		void player_action(int); // determines if the player stays or not
		void print_community();
		void print_players(int);
		int determine_winner();


	private:
		vector<Player> playerVec;
		vector<Card> communityVec;
		int numPlayers;
		CardDeck deck;
        //unordered_map<int, int> *flushesPTR;
        //unordered_map<int, int> *othersPTR;
		//int winner;

};

#endif

