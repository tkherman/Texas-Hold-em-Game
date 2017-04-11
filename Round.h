// Round.h
// This is the class interface for Round class which allow the playing of a round
#include <vector>
#include <iostream>
#include <algorithm>
#include "CardDeck.h"
#include "handTable.h"
using namespace std;

#ifndef ROUND_H
#define ROUND_H

struct Player {
    Card hand[2];
    int playerNum;
    bool in_out;
    int best_rank;
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
		double getOdds(Card hand[2], vector<Card> communityVec, int playersLeft);
		void determine_winner(unordered_map<int, int>&, unordered_map<int, int>&);
        void determine_best_rank(int, unordered_map<int, int>&, unordered_map<int, int>&);

	private:
		vector<Player> playerVec;
		vector<Card> communityVec;
		int numPlayers;
		CardDeck deck;

};

#endif

