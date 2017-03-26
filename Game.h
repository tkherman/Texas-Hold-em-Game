// Game.h
//This is the interface for the game class for our simulated poker game

#include <vector>
#include "CardDeck.h"

#ifndef CARDDECK_H
#define CARDDECK_H

struct Player {
    double money;
    vector<Card> hand;
    
    void resetHand() {
        hand.clear();
    }
}

class Game{

    public:
        Game();
        ~Game();
        void playHand();
    private:
        int numPlayers;
        vector<Player> playersVec;
        //many helper functions to be added
};

#endif
