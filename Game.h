// Game.h
// This is the interface for the game class for our simulated poker game
// This class documents how many players are in the game and continuously 
// call round and record the result.

#include <vector>
#include "CardDeck.h"
#include "Round.h"
#include "handTable.h"

#ifndef GAME_H
#define GAME_H


class Game{

    public:
        Game();
        ~Game();
        void playRound();
		vector<Player> createPlayerVector(int);

    private:
        int numPlayers;
		vector<Player> players;
		unordered_map<int, int> flushes, others;
};

#endif
