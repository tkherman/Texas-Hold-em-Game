// Round.cpp
// This is the implementation of the Round class

#include "Round.h"
#include "oddCalc.h" //include odd calculation functions


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
	if (playersLeft > 1) {
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
	if (playersLeft > 1) {
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
	if (playersLeft > 1) {
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
	
    if (playersLeft > 1)
        determine_winner(playerVec, flushes, others);
    else if (playersLeft == 1) {
        for (auto it = playerVec.begin(); it != playerVec.end(); it++)
            if (it->in_out)
                cout << "player" << it->playerNum << " wins" << endl;
    } else
        cout << "Why are you even playing if you all fold in pre-flop!?!?" << endl;

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
        if (it->in_out && it->best_rank < winning_rank) 
            winning_rank = it->best_rank;
    }

    
    // print out players with highest rank
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->in_out && it->best_rank == winning_rank)
            cout << "player" << it->playerNum << " wins" << endl;
    }

}

