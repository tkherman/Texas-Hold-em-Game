// This is the function implementation for oddCalc

#include "oddCalc.h"
using namespace std;


// This function calculates the max_prime of each player
int determine_best_rank(Card hand[2], vector<Card> community, 
		unordered_map<int, int>&flushes, unordered_map<int, int>&others) {

    // add all seven cards to poss_comb
    vector<Card> poss_comb = community;
    poss_comb.push_back(hand[0]);
    poss_comb.push_back(hand[1]);

    
    // initialize ranking to lowest
    int rank = MAX_RANK;
    
    // not the most graceful way but definitely gets the job done
    for (int i1 = 0; i1 < poss_comb.size() - 4; i1++) {
        for (int i2 = i1 + 1; i2 < poss_comb.size() - 3; i2++) {
            for (int i3 = i2 + 1; i3 < poss_comb.size() - 2; i3++) {
                for (int i4 = i3 + 1; i4 < poss_comb.size() - 1; i4++) {
                    for (int i5 = i4 + 1; i5 < poss_comb.size(); i5++) {
                        bool flushesORnot;
                        char suit = poss_comb[i1].suit;
                        // determine if all cards are flushes
                        if (poss_comb[i2].suit == suit && poss_comb[i3].suit == suit && 
                        poss_comb[i4].suit == suit && poss_comb[i5].suit == suit)
                            flushesORnot = true;
                        else flushesORnot = false;
                        // multiplies all the prime values
                        int temp_prime = poss_comb[i1].prime_value * poss_comb[i2].prime_value *
                        poss_comb[i3].prime_value * poss_comb[i4].prime_value * poss_comb[i5].prime_value;

                        int temp_rank = searchRank(temp_prime, flushesORnot, flushes, others);
                        rank = (rank > temp_rank)? temp_rank : rank;

                    }
                }
            }
        }
    }
    
    return rank;
}

// This function runs a random simulation of the rest of the hand.
// It is used to calculate odds (process called Monte Carlo simulation).
int monteCarlo(CardDeck myDeck, Card hand[2], vector<Card> community,
		unordered_map<int,int> &flushes, unordered_map<int,int> &others, int &playersLeft) {
	
	//shuffle deck for randomization
	myDeck.shuffle();

	//similar to deal function, deal out cards
	vector<Player> playerCards;

	//deal cards to player who's odds we're determining and add to player vector
	Player our_player;
	our_player.hand[0] = hand[0];
    our_player.hand[1] = hand[1];
    our_player.playerNum = 0;
    our_player.in_out = true;
    our_player.best_rank = MAX_RANK;
    our_player.cash_balance = 0;
    playerCards.push_back(our_player);
	//deal cards to everyone else
	for (int i = 1; i < playersLeft; i++) {
		Player temp_player;
		temp_player.playerNum = i;
		temp_player.hand[0] = myDeck.getCard();
		temp_player.hand[1] = myDeck.getCard();
		temp_player.in_out = true;
		playerCards.push_back(temp_player);
	}
	

	//fill community card vector
	while(community.size() < 5)
		community.push_back(myDeck.getCard());

	//same as determine_winner function
	//find the max prime of players that are still in
    for (auto it = playerCards.begin(); it != playerCards.end(); it++) {
        it->best_rank = determine_best_rank(it->hand, community, flushes, others);
    }

    //determine the highest rank
    int winning_rank = MAX_RANK;
    for (auto it = playerCards.begin(); it != playerCards.end(); it++) {
        if (it->best_rank < winning_rank) winning_rank = it->best_rank;
    }

    //loss
	if(playerCards[0].best_rank > winning_rank) return -1;

	//check for ties
	for(int k=1; k<playerCards.size(); k++) {
		if(playerCards[k].best_rank == winning_rank)
			return 0;
	}

	//a win
	return 1;
}

// This function calculates the odds of a player winning
double getOdds(Card hand[2], vector<Card> community, unordered_map<int,int> &flushes, 
			unordered_map<int,int> &others, int playersLeft) {

	//instantiate a card deck
	CardDeck myDeck;

	//remove cards already out or in the hand from deck
	myDeck.remove(hand[0]);
	myDeck.remove(hand[1]);
	for(int k=0; k<community.size(); k++)
		myDeck.remove(community[k]);
	
	//run simulations
	int wins = 0, losses = 0, ties = 0;
	for(int k=0; k<10000; k++) {
		int result = monteCarlo(myDeck, hand, community, flushes, others, playersLeft);
		//result will only be -1, 0, or 1
		switch(result) {
			case -1:
				losses++;
				break;
			case 0:
				ties++;
				break;
			case 1:
				wins++;
				break;
		}
	}

	double winPct = 1.0 * wins / (wins + losses + ties);
	return winPct;

}
