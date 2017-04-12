// Round.cpp
// This is the implementation of the Round class

#include "Round.h"


Round::Round(int n, unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
	/* initialize variables */
    numPlayers = n;
    playersLeft = numPlayers;
    

	/* first step: deal cards to each player, determine who's in and out*/
	deal(numPlayers);
	for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
		if (it->in_out) {
			print_players(it->playerNum);
			cout << getOdds(it->hand, communityVec, flushes, others, numPlayers) << endl;
			player_action(it->playerNum);
		}
	}


	/* if there is more than 1 player, do initial flop and determines who's still in */
	if (playerVec.size() > 1) {
		for (int i = 0; i < 3; i++) {
			flop();
		}
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				cout << getOdds(it->hand, communityVec, flushes, others, playersLeft) << endl;
				player_action(it->playerNum);
			}
		}
	}
	

	/* if there is more than 1 player, do another flop and determines who's still in */
	if (playerVec.size() > 1) {
		flop();
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				cout << getOdds(it->hand, communityVec, flushes, others, playersLeft) << endl;
				player_action(it->playerNum);
			}
		}
	}
	


	/* if there is more than 1 player, do the final flop, determines who's still in */
	if (playerVec.size() > 1) {
		flop();
		print_community();
		for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
			if (it->in_out) {
				print_players(it->playerNum);
				cout << getOdds(it->hand, communityVec, flushes, others, playersLeft) << endl;
				player_action(it->playerNum);
			}
		}
	}
	
    
    //if (playersLeft > 1) 
    	determine_winner(playerVec, flushes, others);

}

Round::~Round() { };

void Round::deal(int num) {
	// create temp_player, assign 2 cards and add temp_player to vector
	for (int i = 0; i < num; i++) {
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
		playersLeft--;
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

void Round::determine_winner(vector<Player> players, unordered_map<int, int>& flushes, 
		unordered_map<int, int>& others) {

    // find the max prime of players that are still in
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->in_out) 
        	it->best_rank = determine_best_rank(it->hand, communityVec, flushes, others);
    }
    
    // determine the highest rank
    int winning_rank = MAX_RANK;
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->best_rank < winning_rank) winning_rank = it->best_rank;
    }
    
    // print out players with highest rank
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->in_out == true && it->best_rank == winning_rank)
            cout << "player" << it->playerNum << " wins" << endl;
    }

}

// This function calculates the max_prime of each player
int Round::determine_best_rank(Card hand[2], vector<Card> community, 
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
int Round::monteCarlo(CardDeck myDeck, Card hand[2], vector<Card> community,
		unordered_map<int,int> &flushes, unordered_map<int,int> &others, int &playersLeft) {
	
	//shuffle deck for randomization
	myDeck.shuffle();

	//similar to deal function, deal out cards
	vector<Player> playerCards;

	//deal cards to player who's odds we're determining and add to player vector
	Player our_player = {hand[0], hand[1], 0, true, MAX_RANK};
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
double Round::getOdds(Card hand[2], vector<Card> community, unordered_map<int,int> &flushes, 
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
