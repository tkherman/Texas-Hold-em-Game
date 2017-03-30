// handTable.cpp
// Contains the implementation of functions in handTable.h,
// reads in card data from ranking file and stores in unordered map


#include "handTable.h"
#include <iostream>


/* This functions loads the rankings of each hands into the two unordered_map */
void loadHandData(unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
	ifstream data("rankings.dat");
	if (data.is_open()) {
		string line;
		int rank = 1;
        // prime value corresponding to card value
		int prime [] = {0, 41, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        
        while (getline(data,line)) {
            int multiple = 1;

            // Convert each card value into prime_value and multiply the multiple
            for (int i = 2; i <= 6; i++) {
                int prime_val = char_to_int(line[i]);
                multiple = multiple * prime[prime_val];
            }

            // add the hand to map
			if(line[0] == '8' || line[0] == '5')  //a flush
				flushes[multiple] = rank++; //increment rank when done
			else
				others[multiple] = rank++;
		}
	}
}

int char_to_int(char cvalue) {
    if (cvalue == 'A') return 1;
    else if (cvalue == 'K') return 13;
    else if (cvalue == 'Q') return 12;
    else if (cvalue == 'J') return 11;
    else if (cvalue == 'T') return 10;
    else return cvalue - '0';
}

int searchRank(int prime_multiple, bool flushesORnot, unordered_map<int, int> &flushes, unordered_map<int, int> &others) {
    if (flushesORnot) return flushes[prime_multiple];
    else return others[prime_multiple];
}

int main() {
    unordered_map<int, int> flushes, others;
    loadHandData(flushes, others);
    //int rank = searchRank(31367009, true, flushes, others);
    cout << flushes[14535931] << endl;
}
