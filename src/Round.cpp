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

/* constructor for round class */
Round::Round(int num, vector<Player>& players, unordered_map<int, int>& flushes, unordered_map<int, int>& others) {
	
	numPlayers = num;
	potBalance = 0;
    owedToPot = 0;
	playersLeft = numPlayers;

    for(int k=0; k<8; k++) potArr[k] = 0;


	//play round
	dealToExisting(players);
	play(flushes, others);

	//assign playerVec to players so the cash values of the vector are carried over
	players = playerVec;

}

Round::~Round() { };

int Round::getNumAllIn() {
    int result = 0;
    for(auto it = playerVec.begin(); it != playerVec.end(); ++it)
        if(it->all_in) result++;
    return result;
}



/* This is a helper function that streamlines the playing of each round */
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
        if(playersLeft - getNumAllIn() > 1)
            betting_round(false, flushes, others);
	}
	

	/* if there is more than 1 player, do another flop and determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        if(playersLeft - getNumAllIn() > 1)
            betting_round(false, flushes, others);
	}
	


	/* if there is more than 1 player, do the final flop, determines who's still in */
	if (playersLeft > 1) {
		flop();
		print_community();
        if(playersLeft - getNumAllIn() > 1)
            betting_round(false, flushes, others);
	}
    
    // determine winner
    if (playersLeft > 1)
        determine_winner(flushes, others);
    else if (playersLeft == 1) {
        for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
            if (it->in_out) {
                cout << "Player" << it->playerNum << " wins!" << endl;
                it->cash_balance += potBalance;
            }
        }
    } else
        cout << "Why are you even playing if you all fold in pre-flop!?!?" << endl;


}

/* deals initial two cards to each player */
// takes in an existing vector of players
// deals cards to each player
// and adds each player to the playerVec of the Round class
void Round::dealToExisting(vector<Player>& players) {
	// create temp_player, assign 2 cards and add temp_player to vector
	for (auto it = players.begin(); it != players.end(); it++) {
		Player temp_player;
		temp_player.playerNum = it->playerNum;
		temp_player.hand[0] = deck.getCard();
		temp_player.hand[1] = deck.getCard();
		temp_player.in_out = true;
        temp_player.computer = it->computer;
		temp_player.cash_balance = it->cash_balance;
		playerVec.push_back(temp_player);
	}
}

/* deals three community cards */
void Round::flop() {
	Card temp_card;
	temp_card = deck.getCard();
	communityVec.push_back(temp_card);
}


/* This function prints out the community cards */
void Round::print_community() {

	// clear screen by printing 10 newline
    for (int i = 0; i < 10; i++) {
        printf("\n");
    }
    
    // create a vector for cards to be printed
    vector<Card> printingVec = communityVec;
    while (printingVec.size() < 5) {
        Card tempC;
        tempC.charVal = ' ';
        tempC.suitIcon = ' ';
        printingVec.push_back(tempC);
    }
    cout << "---------------Community Cards-----------------" << endl;
	char stringToBePrinted[700];
    sprintf(stringToBePrinted,
    " -----------   -----------   -----------   -----------   ----------- \n\
|%c%c         | |%c%c         | |%c%c         | |%c%c         | |%c%c         |\n\
|           | |           | |           | |           | |           |\n\
|           | |           | |           | |           | |           |\n\
|     %c     | |      %c    | |     %c     | |     %c     | |     %c     |\n\
|           | |           | |           | |           | |           |\n\
|           | |           | |           | |           | |           |\n\
|         %c%c| |         %c%c| |         %c%c| |         %c%c| |         %c%c|\n\
 -----------   -----------   -----------   -----------   ----------- " 
    , printingVec[0].charVal, printingVec[0].suitIcon, printingVec[1].charVal, printingVec[1].suitIcon
    , printingVec[2].charVal, printingVec[2].suitIcon, printingVec[3].charVal, printingVec[3].suitIcon
    , printingVec[4].charVal, printingVec[4].suitIcon
    , printingVec[0].suitIcon, printingVec[1].suitIcon, printingVec[2].suitIcon, printingVec[3].suitIcon
    , printingVec[4].suitIcon
    , printingVec[0].charVal, printingVec[0].suitIcon, printingVec[1].charVal, printingVec[1].suitIcon
    , printingVec[2].charVal, printingVec[2].suitIcon, printingVec[3].charVal, printingVec[3].suitIcon
    , printingVec[4].charVal, printingVec[4].suitIcon
    );
    printf("%s", stringToBePrinted);

    
    /*for (auto it = communityVec.begin(); it != communityVec.end(); it++) {
		it->display();
		cout << " || ";
	}*/
    

	cout << endl << endl << endl;
}



/* prints the hand of a particulat player */
void Round::print_players(int playerN) {
	cout << "player" << playerN << ":" << endl;
    char stringToBePrinted[300];
    sprintf(stringToBePrinted,
    " -----------   ----------- \n\
|%c%c         | |%c%c         |\n\
|           | |           |\n\
|           | |           |\n\
|     %c     | |      %c    |\n\
|           | |           |\n\
|           | |           |\n\
|         %c%c| |         %c%c|\n\
 -----------   ----------- " 
    , playerVec[playerN].hand[0].charVal, playerVec[playerN].hand[0].suitIcon
    , playerVec[playerN].hand[1].charVal, playerVec[playerN].hand[1].suitIcon
    , playerVec[playerN].hand[0].suitIcon, playerVec[playerN].hand[1].suitIcon
    , playerVec[playerN].hand[0].charVal, playerVec[playerN].hand[0].suitIcon
    , playerVec[playerN].hand[1].charVal, playerVec[playerN].hand[1].suitIcon
    );
    printf("%s", stringToBePrinted);
    cout << endl;
}



/* This function determines the winner of a hand*/
void Round::determine_winner(unordered_map<int, int>& flushes, 
		unordered_map<int, int>& others) {


    // find the max prime of players that are still in
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out) 
        	it->best_rank = determine_best_rank(it->hand, communityVec, flushes, others);
    }
    

    // determine the number of players all in
    int numAllIn = 0;
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->all_in)
            numAllIn++;
    }
    
    
    
    // print out players with highest rank
    int numberOfWinners, winning_rank;
    vector<Player>::iterator start_it = playerVec.begin();
    vector<Player>::iterator it = playerVec.begin();



    numberOfWinners = 0;
    do {
        if(potBalance <= 0) break; //done checking who won - all money given out

        //determine the highest rank
        winning_rank = MAX_RANK;
        for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
            if (it->in_out && it->best_rank < winning_rank) 
                winning_rank = it->best_rank;
        }

        if (it->in_out && it->best_rank == winning_rank) {
            cout << "Player" << it->playerNum << " wins" << endl;

            //check if all in
            if(it->all_in) {
                

                //determine amount of winnings

                //initialize to equal pot balance
                double winnings = potBalance;
                for(auto ptr = playerVec.begin(); ptr != playerVec.end(); ++ptr) {
                    if(ptr->in_out) {
                        double amt = potArr[it->playerNum] - potArr[ptr->playerNum];
                        if(amt > 0) winnings -= amt;
                    }
                }


                it->cash_balance += winnings;
                cout << "All in, so Player" << it->playerNum << " wins ";
                cout << winnings << endl;
                numAllIn--;



                //adjust pot balance and make player out
                //potBalance -= potArr[it->playerNum];
                potBalance -= winnings;
                numberOfWinners--;
                it->in_out = false;
                it->all_in = false; //accounted for, so set to false

                //reset start_it
                start_it = it;
            }

            numberOfWinners++;
        } 
        //increment it
        ++it;
        if(it == playerVec.end()) it = playerVec.begin();

    } while(it != start_it);


    double split_pot = potBalance/numberOfWinners;

    // add balance to winning player(s)
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->in_out && it->best_rank == winning_rank) {
            it->cash_balance += split_pot;
        }
    }

}


/* this function determines the number of players at a certain rank value */
int Round::getNumAtRank(int rank) {
    int result = 0;
    for (auto it = playerVec.begin(); it != playerVec.end(); it++) {
        if (it->best_rank == rank) {
            result++;
        }
    }
    return result;
}



/* this function implements a betting round */
void Round::betting_round(bool ante, unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
    string input;

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

            //check for out of money
            if(it->cash_balance <= ANTE) {
                potBalance += it->cash_balance;
                owedToPot += ANTE; //payed less than owed
                potArr[it->playerNum] += it->cash_balance;
                it->cash_balance = 0;
                it->all_in = true;

            } else {
                it->cash_balance -= ANTE;
                potArr[it->playerNum] += ANTE;
                potBalance += ANTE;
                owedToPot += ANTE; //paid what owed
            }

            
            
        }
    }

    //actual value of this doesn't matter - just the diff w/ potArr
    //so initialize to the max of potArr
    int betInRound = 0;
    for(auto it = playerVec.begin(); it != playerVec.end(); ++it) {
        if(potArr[it->playerNum] > betInRound)
            betInRound = potArr[it->playerNum];
    }
    int origInRound = betInRound;

    int raise_no = 1;

    vector<Player>::iterator start_it = playerVec.begin();
    vector<Player>::iterator it = playerVec.begin();

    while(!settled) {
        outer_increment = true;
        
            

        if (it->in_out && !it->all_in) {
            // do this printing if player isn't computer
            if (it->computer == false) {
				
                print_players(it->playerNum);

                cout << "Chance of winning: " << getOdds(it->hand, communityVec, flushes, others, numPlayers) << endl;
                cout << "You have $" << it->cash_balance << endl;
                cout << "Total amount in pot $" << potBalance << endl;
            } else {
                cout << "Player" << it->playerNum << " has $" << it->cash_balance << endl;
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
                        int AI_decision = AI_determine(handstrength, betInRound - origInRound, potBalance);
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
                        {
                            //check for out of money
                            if(it->cash_balance <= FIXED_LIMIT) {
                                potBalance += it->cash_balance;
                                owedToPot += FIXED_LIMIT; //paid less than owed
                                betInRound += it->cash_balance;
                                potArr[it->playerNum] += it->cash_balance;
                                cout << "Putting in: $" << it->cash_balance << endl;
                                cout << "Player" << it->playerNum << " is all in!\n";
                                it->cash_balance = 0;
                                it->all_in = true;
                            }
                            else {
                                it->cash_balance -= FIXED_LIMIT;
                                potArr[it->playerNum] += FIXED_LIMIT;
                                potBalance += FIXED_LIMIT;
                                owedToPot += FIXED_LIMIT; //paid what owed
                                betInRound += FIXED_LIMIT;
                                cout << "Putting in: $" << FIXED_LIMIT << endl;
                            }
                            
                            // change start_it since it must go all the way around the table again
                            start_it = it;
                            it++;
                            if (it == playerVec.end())
                                it = playerVec.begin();

                            outer_increment = false;
                            options = calling;

                            corr_input = true;
                        }
                            break;
                        case raise:
                            cout << "Invalid input, you can't raise since no one has bet." << endl;
                            break;
                        case call:
                        case invalid:
                            cout << "Invalid input, please try again." << endl;
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
                        int AI_decision = AI_determine(handstrength, betInRound - origInRound, potBalance);
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
                        {

                            adding_amount = betInRound - potArr[it->playerNum];

                            //check for out of money
                            if(it->cash_balance <= adding_amount) {
                                potBalance += it->cash_balance;
                                owedToPot += adding_amount; //paid less than owed
                                potArr[it->playerNum] += it->cash_balance;
                                cout << "Putting in: $" << it->cash_balance << endl;
                                cout << "Player" << it->playerNum << " is all in!\n";
                                it->cash_balance = 0;
                                it->all_in = true;
                            }
                            else {
                                it->cash_balance -= adding_amount;
                                potArr[it->playerNum] += adding_amount;
                                potBalance += adding_amount;
                                owedToPot += adding_amount; //paid what owed
                                //betInRound += adding_amount;
                                cout << "Putting in: $" << adding_amount << endl;
                            }

                            corr_input = true;
                        }
                            break;
                        case raise:
                            // reached raise cap, ask for input again
                            if (raise_no > RAISE_CAP) {
                                cout << "Reaching raise cap, cannot raise again. Please input "
                                    << "another  option." << endl;
                                break;
                            }

                            //deal with the money
                            adding_amount = betInRound - potArr[it->playerNum] + FIXED_LIMIT;

                            //check for out of money
                            if(it->cash_balance <= adding_amount) {
                                potBalance += it->cash_balance;
                                owedToPot += adding_amount; //paid less than owed
                                betInRound += it->cash_balance;
                                potArr[it->playerNum] += it->cash_balance;
                                cout << "Putting in: $" << it->cash_balance << endl;
                                cout << "Player" << it->playerNum << " is all in!\n";
                                it->cash_balance = 0;
                                it->all_in = true;
                            }
                            else {
                                it->cash_balance -= adding_amount;
                                potArr[it->playerNum] += adding_amount;
                                potBalance += adding_amount;
                                owedToPot += adding_amount; //paid what owed
                                betInRound += FIXED_LIMIT;
                                cout << "Putting in: $" << adding_amount << endl;
                            }  


                            // change start_it since it must go all the way around the table again
                            start_it = it;
                            it++;
                            if (it == playerVec.end())
                                it = playerVec.begin();

                            outer_increment = false;

                            raise_no++; //increment raise count
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

            if (it->all_in) 
                cout << "Player" << it->playerNum << " is all in" << endl;

            it++;
            if (it == playerVec.end()) // ensure it goes around the table
                it = playerVec.begin();
            if (it == start_it || playersLeft == 1) //check if over
                settled = true;
        }
    }
}

