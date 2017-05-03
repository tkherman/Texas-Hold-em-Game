// Game.cpp
// This is the implementation of the game class

#include "Game.h"

vector<Player> createPlayerVector(int);

Game::Game() {
	
	//ask user for number of players

	numPlayers = 0; //initialize out of bounds
	cout << "How many computer players? ";
	cin >> numPlayers;
    numPlayers++; // add one extra for actual player

	//check for failure
	if(!cin) {
		cin.clear();
		cin.ignore(999, '\n');
	}
	while(numPlayers < 2 || numPlayers > 8) {
		cout << "Invalid number of players, please try again: ";
		cin >> numPlayers;
		if(!cin) {
			cin.clear();
			cin.ignore(999, '\n');
		}
	}
	

	//load player vector
	players = createPlayerVector(numPlayers);
	
	//initialize flushes and others maps
	loadHandData(flushes, others);

	//loop for playing rounds
	do {
		cout << "New Round" << endl;
		cout << "----------------\n\n";

		playRound();

		//check if anyone's out of cash
		cout << "\n------------" << endl;
		for(int k=0; k<numPlayers; k++) {
			
			//display each player's total after the round
			cout << "Player " << players[k].playerNum << " has $";
			cout << players[k].cash_balance << endl;

			//if anyone's out of money, remove them from the game
			if(players[k].cash_balance <= 0) {
				cout << "Player " << players[k].playerNum << " eliminated." << endl;
				
				//remove player while preserving order
				int index = k + 1, trail = k;
				while(index < numPlayers) {
					players[trail] = players[index];
					index++; trail++;
				}
				players.pop_back();
				k--; //change the loop condition to deal w/pop back
				numPlayers--;
			}

		}
		cout << endl << "----Round Over----" << endl << endl;
		
		cout << "Press enter to continue." << endl << endl;
		cin.ignore(); cin.get();
		for(int k=0; k<5; k++) cout << "\n\n\n\n\n\n\n\n\n\n";

		//rotate players for next round
		rotatePlayerVector();

	} while(numPlayers >= 2);

	cout << "Game over. Player " << players[0].playerNum << " wins!" << endl;
}

//deconstructor
Game::~Game() {}

vector<Player> Game::createPlayerVector(int num) {
	vector<Player> result;
    Player human;
    human.playerNum = 0;
    human.computer = false;
    result.push_back(human);
	for(int k=1; k < num; k++) {
		Player temp;
		temp.playerNum = k;
        temp.computer = true;
		result.push_back(temp);
	}
	return result;
}

void Game::playRound() {
	Round r(numPlayers, players, flushes, others);
}

void Game::rotatePlayerVector() {
	int trail = 0, lead = 1;
	Player temp = players[0];
	while(lead < numPlayers) {	
		players[trail] = players[lead];
		trail++; lead++;
	}
	players[trail] = temp; //move from back to front
}
