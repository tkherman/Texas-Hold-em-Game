// Game.cpp
// This is the implementation of the game class

#include "Game.h"

vector<Player> createPlayerVector(int);

Game::Game() {
	
	//ask user for number of players

	numPlayers = 0; //initialize out of bounds
	cout << "How many players? ";
	cin >> numPlayers;
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
		playRound();

		//check if anyone's out of cash
		cout << "------------" << endl;
		for(int k=0; k<players.size(); k++) {
			
			//display each player's total after the round
			cout << "Player " << players[k].playerNum << " has $";
			cout << players[k].cash_balance << endl;

			//if anyone's out of money, remove them from the game
			if(players[k].cash_balance <= 0) {
				cout << "Player " << players[k].playerNum << " eliminated." << endl;
				players[k] = players[players.size()-1];
				players.pop_back();
				numPlayers--;
			}

		}
		cout << endl << "----Round Over----" << endl << endl;

	} while(numPlayers >= 2);
}

//deconstructor
Game::~Game() {}

vector<Player> Game::createPlayerVector(int num) {
	vector<Player> result;
	for(int k=0; k < num; k++) {
		Player temp;
		temp.playerNum = k;
		result.push_back(temp);
	}
	return result;
}

void Game::playRound() {
	cout << flushes.size() << endl;
	Round r(numPlayers, players, flushes, others);
}
