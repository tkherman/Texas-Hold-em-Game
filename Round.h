// Round.h
// This is the class interface for Round class which allow the playing of a round

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <cstdio>
#include "CardDeck.h"
#include "handTable.h"
#include "oddCalc.h"
#include "AI.h"

using namespace std;

#ifndef ROUND_H
#define ROUND_H

#define ANTE 5
#define FIXED_LIMIT 20
#define RAISE_CAP 2


typedef enum {
    fold,
    check,
    bet,
    call,
    raise,
    invalid,
}PlayerAction;

PlayerAction hashit(const string &input);


class Round {
	public:
		Round(int, unordered_map<int, int>&, unordered_map<int, int>&); // initialize players
		Round(int, vector<Player>&, unordered_map<int, int>&, unordered_map<int, int>&);
		~Round();
		void play(unordered_map<int, int>&, unordered_map<int, int>&);
		void deal(int); // for each player, deal 2 cards
		void dealToExisting(vector<Player>&); //for use in Game class
		void flop();
        //void ante(unordered_map<int, int>&, unordered_map<int, int>&);
        void betting_round(bool, unordered_map<int, int>&, unordered_map<int, int>&);
		void print_community();
		void print_players(int);


		void determine_winner(/*vector<Player>,*/ unordered_map<int, int>&, 
			unordered_map<int, int>&);

		
	private:
		vector<Player> playerVec;
		vector<Card> communityVec;
		int numPlayers;
		int playersLeft;
		CardDeck deck;
        int potBalance;
};

#endif

