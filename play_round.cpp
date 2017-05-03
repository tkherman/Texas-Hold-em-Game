// test_round.cpp
// driver to test the round class

#include <iostream>
#include "Round.h"
#include "handTable.h"


int main() {
	unordered_map<int, int> flushes, others;
    loadHandData(flushes, others);
	cout << flushes.size() << endl;
    //Round r(3, flushes, others);

	/*testing second constructor*/
	vector<Player> players;
	//load player vector with numbers
	for(int k=0; k<3; k++) {
		Player temp;
		temp.playerNum = k;
		players.push_back(temp);
	}


	Round rnd(3, players, flushes, others);

	//test if player vec was changed (this was successful)
	/*for(auto it = players.begin(); it != players.end(); it++)
		cout << it->cash_balance << endl;
	*/
}
