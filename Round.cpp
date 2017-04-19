// Round.cpp
// This is the implementation of the Round class

#include "Round.h"

PlayerAction hashit(const string &input) {
    if (input == "fold") return fold;
    else if (input == "check") return check;
    else if (input == "bet") return bet;
    else if (input == "call") return call;
    else if (input == "raise") return raise;
    else return invalid;
}

Round::Round(int n, unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
	/* initialize variables */
    numPlayers = n;
    playersLeft = numPlayers;
    

	/* first step: deal cards to each player, determine who's in and out*/
	deal(numPlayers);
    ante(flushes, others);


	/* if there is more than 1 player, do initial flop and determines who's still in */
	if (playersLeft > 1) {
		for (int i = 0; i < 3; i++) {
			flop();
		}
		print_community();
        betting_round(flushes, others);
	}
	

	/* if there is more than 1 player, do another flop and determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        betting_round(flushes, others);
	}
	


	/* if there is more than 1 player, do the final flop, determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        betting_round(flushes, others);
	}
    
    // determine winner
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
/*void Round::player_action(int pNum) {
	char input;
	cout << "fold or stay in? f for fold, s for stay: ";
	cin >> input;
	if (input == 'f') {
		playerVec[pNum].in_out = false;
		playersLeft--;
	}
}*/

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

void Round::ante(unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
    string input;

    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        print_players(it->playerNum);
        cout << "Chance of winning: " << getOdds(it->hand, communityVec, flushes, others, numPlayers) << endl;

        // ask for user input depending on raising flag
        bool corr_input = false; // flag to check if user is inputing right
        while (!corr_input) {
            cout << "Do you wish to check, or fold? ";
            cin >> input;
        
            switch(hashit(input)) {
                case fold:
                    it->in_out = false;
                    it->cash_balance -= ANTE;
                    potArr[it->playerNum] += ANTE;
                    corr_input = true;
                    break;
                case check:
                    it->cash_balance -= ANTE;
                    potArr[it->playerNum] += ANTE;
                    corr_input = true;
                    break;
                case invalid:
                case bet:
                case call:
                case raise:
                    cout << "Invalid input, please try again" << endl;
                    break;
            }
        }
    }
}

void Round::betting_round(unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
    string input;
    bool settled = false; // flag to see if we've gone around the table
    bool can_check = true; // flag to see if player can check

    vector<Player>::iterator it = playerVec.begin();
    while(!settled) {
        if (it->in_out) {
            print_players(it->playerNum);
            cout << "Chance of winning: " << getOdds(it->hand, communityVec, flushes, others, numPlayers) << endl;
        
            // ask for user input depending on raising flag
            bool corr_input = false; // flag to check if user is inputing right
            while (!corr_input) {
                cout << "Do you wish to fold, bet, call, or raise? ";
                cin >> input;
        
                switch(hashit(input)) {
                    case check:
                        if (!can_check) {
                            cout << "Must call, raise or fold" << endl;
                            break;
                        }
                        corr_input = true;
                        break;
                    case fold:
                        it->in_out = false;
                        corr_input = true;
                        break;
                    case bet:
                        it->cash_balance -= FIXED_LIMIT;
                        potArr[it->playerNum] += FIXED_LIMIT;
                        corr_input = true;
                        break;
                    case call:
                        it->cash_balance -= FIXED_LIMIT;
                        potArr[it->playerNum] += FIXED_LIMIT;
                        corr_input = true;
                        break;
                    case raise:
                        it->cash_balance -= (FIXED_LIMIT * 2);
                        potArr[it->playerNum] += (FIXED_LIMIT * 2);
                        raising(it->playerNum, 1, flushes, others);
                        settled = true;
                        corr_input = true;
                        break;
                    case invalid:
                        cout << "Invalid input, please try again" << endl;
                        break;
                }
            }
        
            it++;
            if (it == playerVec.end())
                settled = true;
        } else {
            it++;
            if (it == playerVec.end())
                settled = true;
        }
    }
}

void Round::raising(int raising_playerNum, int raise_no, unordered_map<int, int> &flushes,
    unordered_map<int, int> &others) {
    string input;
    bool settled = false;
    
    // initialize itertor, move to one after the raising player
    vector<Player>::iterator raising_it = playerVec.begin();
    for (int i = 0; i < raising_playerNum; i++) 
        raising_it++; // this moves to raising player
    
    // moves to the one after raising player
    vector<Player>::iterator it = raising_it + 1;
    
    
    while (!settled) {
        if (it->in_out) {
            int adding_amount;
            // ask for user input depending on raising flag
            bool corr_input = false; // flag to check if user is inputing right
            while (!corr_input) {
                cout << "Do you wish to fold, bet, call, or raise? ";
                cin >> input;
        
                switch(hashit(input)) {
                    case check:
                        cout << "A player has raise, you must call, raise or fold" << endl;
                        break;
                    case fold:
                        it->in_out = false;
                        corr_input = true;
                        break;
                    case bet:
                        adding_amount = potArr[raising_it->playerNum] - potArr[it->playerNum];
                        it->cash_balance -= adding_amount;
                        potArr[it->playerNum] += adding_amount;
                        corr_input = true;
                        break;
                    case call:
                        adding_amount = potArr[raising_it->playerNum] - potArr[it->playerNum];
                        it->cash_balance -= adding_amount;
                        potArr[it->playerNum] += adding_amount;
                        corr_input = true;
                        break;
                    case raise:
                        // reached raise cap, ask for input again
                        if (raise_no > 4) {
                            cout << "Reaching raise cap, cannot raise again. Please input "
                                << "another  option." << endl;
                        break;
                        }
                    
                        // calculate total amount including raising, then call raising again
                        adding_amount = potArr[raising_it->playerNum] - potArr[it->playerNum] + FIXED_LIMIT;
                        it->cash_balance -= adding_amount;
                        potArr[it->playerNum] += adding_amount;
                        raising(it->playerNum, raise_no++, flushes, others);
                        corr_input = true;
                        break;
                    case invalid:
                        cout << "Invalid input, please try again" << endl;
                        break;
                }
            }

            it++;
            if (it == playerVec.end())
                it = playerVec.begin();
            else if (it == raising_it)
                settled = true;
        } else {
            it++;
            if (it == playerVec.end())
                it = playerVec.begin();
            else if (it == raising_it)
                settled = true;
        }
    }
}
