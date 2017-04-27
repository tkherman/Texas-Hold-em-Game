// Round.cpp
// This is the implementation of the Round class

#include "Round.h"


/* This function returns a decision
There are two possible set of decision:
1) when no one has bet, so AI has the option to fold, check or bet
2) when someone has bet/raised, so AI has the option to fold, call, raise

The return value can be 0, 1, 2 where:
0 always represent fold
1 can represent check or call
2 represent bet or raise
*/ 
int AI_determine(double handStrength, int bet, int pot) { 

    // calculate pot odd
    double sum = bet + pot;
    double potOdd = (double)bet/sum;

    // calculate rate of return
    double RR = handStrength/potOdd;

    /* Now with the pot odd and rate of return, a decision can be made based
    on that using percentage and chance:
    Let follow this initial logic:
    If RR < 0.8 then 95% fold, 0 % call, 5% raise (bluff)
    If RR < 1.0 then 80%, fold 5% call, 15% raise (bluff)
    If RR <1.3 the 0% fold, 60% call, 40% raise
    Else (RR >= 1.3) 0% fold, 30% call, 70% raise
    If fold and amount to call is zero, then call.*/
    
    cout << "bet: " << bet << ", pot: " << pot << endl;
    cout << "sum: " << sum << endl;
    cout << "potOdd: " << potOdd << endl;
    cout << "handStrength: " << handStrength << endl;
    cout << "RR: " << RR << endl;

    
    // generate a random number between 0-99
    int randNum = rand() % 100;
    
    
    // deals with the case when no one has bet
    if (bet == 0) {
        if (handStrength > 0.6)
            if (randNum < 70)
                return 2;
            else
                return 1;
        else
            return 1;
    }

    // assign 0-94 to fold, 95-99 to raise and likewise for others
    if (RR < 0.8) {
        if (randNum < 95)
            return 0;
        else
            return 2;
    } else if (RR < 1.0) {
        if (randNum < 80)
            return 0;
        else if (randNum >= 80 && randNum <85)
            return 1;
        else
            return 2;
    } else if (RR < 1.3) {
        if (randNum < 60)
            return 1;
        else
            return 2;
    } else if (RR < 100) { 
        if (randNum < 30)
            return 1;
        else
            return 2;
    } else { // case where no one has bet, RR would be inf
        // > 38% chance of winning, 40% bet, 60% check
        if (handStrength > 0.38)
            if (randNum < 50)
                return 2;
            else 
                return 1;
        else
            return 1;
    }
}


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
    
	/* play round */
	deal(numPlayers);
	play(flushes, others);
}

//to be used in game class
Round::Round(int num, vector<Player>& players, unordered_map<int, int>& flushes, unordered_map<int, int>& others) {
	
	numPlayers = num;
	playersLeft = numPlayers;

	//play round
	dealToExisting(players);
	play(flushes, others);

	//assign playerVec to players so the cash values of the vector are carried over
	players = playerVec;

}

Round::~Round() { };


void Round::play(unordered_map<int, int>& flushes, unordered_map<int, int>& others) {
    // randomize seed for AI
    srand(time(NULL));


	/* first step: determine who's in and out*/
    betting_round(true, flushes, others);


	/* if there is more than 1 player, do initial flop and determines who's still in */
	if (playersLeft > 1) {
		for (int i = 0; i < 3; i++) {
			flop();
		}
		print_community();
        betting_round(false, flushes, others);
	}
	

	/* if there is more than 1 player, do another flop and determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        betting_round(false, flushes, others);
	}
	


	/* if there is more than 1 player, do the final flop, determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        betting_round(false, flushes, others);
	}
    
    // determine winner
    if (playersLeft > 1)
        determine_winner(flushes, others);
    else if (playersLeft == 1) {
        for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
            if (it->in_out) {
                cout << "player" << it->playerNum << " wins" << endl;
                it->cash_balance += potBalance;
            }
        }
    } else
        cout << "Why are you even playing if you all fold in pre-flop!?!?" << endl;


}

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

void Round::dealToExisting(vector<Player>& players) {
	// create temp_player, assign 2 cards and add temp_player to vector
	for (auto it = players.begin(); it != players.end(); it++) {
		Player temp_player;
		temp_player.playerNum = it->playerNum;
		temp_player.hand[0] = deck.getCard();
		temp_player.hand[1] = deck.getCard();
		temp_player.in_out = true;
        temp_player.computer = it->computer;
		playerVec.push_back(temp_player);
	}
}

void Round::flop() {
	Card temp_card;
	temp_card = deck.getCard();
	communityVec.push_back(temp_card);
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

void Round::determine_winner(unordered_map<int, int>& flushes, 
		unordered_map<int, int>& others) {


    // find the max prime of players that are still in
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out) 
        	it->best_rank = determine_best_rank(it->hand, communityVec, flushes, others);
    }
    

    // determine the highest rank
    int winning_rank = MAX_RANK;
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out && it->best_rank < winning_rank) 
            winning_rank = it->best_rank;
    }
    
    int numberOfWinners = 0;
    
    // print out players with highest rank
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out && it->best_rank == winning_rank) {
            cout << "player" << it->playerNum << " wins" << endl;
            numberOfWinners++;
        }
    }

    int split_pot = potBalance/numberOfWinners;

    // add balance to winning player(s)
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out && it->best_rank == winning_rank) {
            it->cash_balance += split_pot;
        }
    }

}


void Round::betting_round(bool ante, unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
    string input;
    
    int potArr[numPlayers];
    // initialize potArr to all 0
    for (int i = 0; i < numPlayers; i++)
        potArr[i] = 0;

    bool settled = false; // flag to see if we've gone around the table
    bool outer_increment;
    
    // used to determine if it's in betting state or calling state
    enum game_options {
        betting,
        calling,
    } options;

    options = betting;

    if (ante == true) { // deduct ante from everyone
        for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
            it->cash_balance -= ANTE;
            potBalance += ANTE;
        }
    }

    int betInRound = 0;
    int raise_no = 1;

    vector<Player>::iterator start_it = playerVec.begin();
    vector<Player>::iterator it = playerVec.begin();

    while(!settled) {
        outer_increment = true;
        if (it->in_out) {
            // do this printing if player isn't computer
            if (it->computer == false) {
                print_players(it->playerNum);
                cout << "Chance of winning: " << getOdds(it->hand, communityVec, flushes, others, numPlayers) << endl;
                cout << "You have $" << it->cash_balance << endl;
                cout << "Total amount in pot $" << potBalance << endl;
            } else {
                cout << "Player" << it->playerNum << "has $" << it->cash_balance << endl;
            }

            if (options == betting) {
                bool corr_input = false; // flag to check if user is inputing right
                while (!corr_input) {
                    // do this if player isn't computer
                    if (it->computer == false) {
                        cout << "Do you wish to fold, check or bet? ";
                        cin >> input;
                    } else {
                        double handstrength = getOdds(it->hand, communityVec, flushes, others, numPlayers);
                        int AI_decision = AI_determine(handstrength, betInRound, potBalance);
                        if (AI_decision == 0) {
                            input = "fold";
                            cout << "Player" << it->playerNum << " folds" << endl;
                        } else if (AI_decision == 1) {
                            input = "check";
                            cout << "Player" << it->playerNum << " checks" << endl;
                        } else if (AI_decision == 2) {
                            input = "bet";
                            cout << "Player" << it->playerNum << " bet" << endl;
                        }
                    }
                     

                    // hashit turns input string into a enum type 
                    switch(hashit(input)) {
                        case check:
                            corr_input = true;
                            break;
                        case fold:
                            it->in_out = false;
                            playersLeft--;
                            corr_input = true;
                            break;
                        case bet:
                            it->cash_balance -= FIXED_LIMIT;
                            potArr[it->playerNum] += FIXED_LIMIT;
                            potBalance += FIXED_LIMIT;
                            betInRound += FIXED_LIMIT;
                            cout << "Putting in: $" << FIXED_LIMIT << endl;
                            
                            // change start_it since it must go all the way around the table again
                            start_it = it;
                            it++;
                            if (it == playerVec.end())
                                it = playerVec.begin();
                            outer_increment = false;
                            options = calling;

                            corr_input = true;
                            break;
                        case raise:
                            cout << "Invalid input, you can't raise since no one has bet" << endl;
                            break;
                        case call:
                        case invalid:
                            cout << "Invalid input, please try again" << endl;
                            break;
                    }
                    cout << endl;
                } 
            } else if (options == calling) {
                bool corr_input = false; // flag to check if user is inputing right
                while (!corr_input) {
                    if (it->computer == false) {
                        cout << "Do you wish to fold, call, or raise? ";
                        cin >> input;
                    } else {
                        double handstrength = getOdds(it->hand, communityVec, flushes, others, numPlayers);
                        int AI_decision = AI_determine(handstrength, betInRound, potBalance);
                        if (AI_decision == 0) {
                            input = "fold";
                            cout << "Player" << it->playerNum << " folds" << endl;
                        } else if (AI_decision == 1) {
                            input = "call";
                            cout << "Player" << it->playerNum << " calls" << endl;
                        } else if (AI_decision == 2) {
                            if (raise_no <= RAISE_CAP) {
                                input = "raise";
                                cout << "Player" << it->playerNum << " raises" << endl;
                            } else {
                                input = "call";
                                cout << "Player" << it->playerNum << " calls" << endl;
                            }
                        }
                    }

                    int adding_amount;
            
                    switch(hashit(input)) {
                        case fold:
                            it->in_out = false;
                            playersLeft--;
                            corr_input = true;
                            break;
                        case call:
                            adding_amount = betInRound - potArr[it->playerNum];
                            it->cash_balance -= adding_amount;
                            potArr[it->playerNum] += adding_amount;
                            potBalance += adding_amount;
                            cout << "Putting in: $" << adding_amount << endl;
                            corr_input = true;
                            break;
                        case raise:
                            // reached raise cap, ask for input again
                            if (raise_no > RAISE_CAP) {
                                cout << "Reaching raise cap, cannot raise again. Please input "
                                    << "another  option." << endl;
                            break;
                            }

                            // deal with the money
                            adding_amount = betInRound - potArr[it->playerNum] + FIXED_LIMIT;
                            it->cash_balance -= adding_amount;
                            potArr[it->playerNum] += adding_amount;
                            potBalance += adding_amount;
                            cout << "Putting in: $ " << adding_amount << endl;
                            betInRound += FIXED_LIMIT;

                            // change start_it since it must go all the way around the table again
                            start_it = it;
                            it++;
                            if (it == playerVec.end())
                                it = playerVec.begin();
                            outer_increment = false;

                            raise_no++;
                            corr_input = true;
                            break;
                        case bet:
                        case check:
                        case invalid:
                            cout << "Invalid input, please try again" << endl;
                            break;
                    }
                    cout << endl;
                }
            }
            
            if (outer_increment) {
                it++;
                if (it == playerVec.end()) // ensure that the it goes around the table
                    it = playerVec.begin();
                if (it == start_it || playersLeft == 1) //check if over
                    settled = true;
            }

        } else {
            it++;
            if (it == playerVec.end()) // ensure it goes around the table
                it = playerVec.begin();
            if (it == start_it || playersLeft == 1) //check if over
                settled = true;
        }
    }
}

