//cardData.h
//reads in card data from ranking file and stores in dictionary

#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
//#include "CardDeck.h"

void loadCardData(map<string,int> &flushes, map<string,int> &others) {
	ifstream data("rankings.dat");
	if (data.is_open()) {
		string line;
		int rank = 1;
		while (getline(data,line)) {

			sort(line.begin()+2, line.end()); //sort hand to standardize
			if(line[0] == '8' || line[0] == '5')  //a flush
				flushes[line.substr(2,5)] = rank++; //increment fct when done
			else
				others[line.substr(2,5)] = rank++;
		}
	}
}

int main() {
	string hand = "KAA5A";
	sort(hand.begin(),hand.end());
	cout << hand << endl;
	map<string,int> flushes, others;
	loadCardData(flushes,others);
	cout << "size: " << sizeof(others) << endl;
	cout << others[hand] << endl;
}

