// play_round.cpp
// driver to test the round class

#include <iostream>
#include "Round.h"
#include "handTable.h"


int main() {
	
	//load in the rankings data into unordered_maps
	unordered_map<int, int> flushes, others;
    loadHandData(flushes, others);

	//load player vector with player numbers
	vector<Player> players;
	for(int k=0; k<3; k++) {
		Player temp;
		temp.playerNum = k;
		players.push_back(temp);
	}
	
	//play the round with 3 players
	//this will not include AI
	Round rnd(3, players, flushes, others);

}
