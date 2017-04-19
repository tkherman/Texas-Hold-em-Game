// Round.h
// This is the class interface for Round class which allow the playing of a round

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "CardDeck.h"
#include "handTable.h"
#include "oddCalc.h"

using namespace std;

#ifndef ROUND_H
#define ROUND_H

#define ANTE 5
#define FIXED_LIMIT 20
#define RAISE_CAP 4


typedef enum {
    fold,
    check,
    bet,
    call,
    raise,
    invalid,
}PlayerAction;

PlayerAction hashit(const string &input);
/*PlayerAction hashit(const string &input) {
    if (input == "fold") return fold;
    else if (input == "check") return check;
    else if (input == "bet") return bet;
    else if (input == "call") return call;
    else if (input == "raise") return raise;
    else return invalid;
}*/


class Round {
	public:
		Round(int, unordered_map<int, int>&, unordered_map<int, int>&); // initialize players
		~Round();
		void deal(int); // for each player, deal 2 cards
		void flop();
        void ante(unordered_map<int, int>&, unordered_map<int, int>&);
        void betting_round(unordered_map<int, int>&, unordered_map<int, int>&);
        void raising(int, int, unordered_map<int, int>&, unordered_map<int, int>&);
		void print_community();
		void print_players(int);


		void determine_winner(vector<Player>, unordered_map<int, int>&, 
			unordered_map<int, int>&);

		
	private:
		vector<Player> playerVec;
		vector<Card> communityVec;
		int numPlayers;
		int playersLeft;
		CardDeck deck;
        int potArr[10]; // let 10 be the max number of players at a table

};

#endif

