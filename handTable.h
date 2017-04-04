// handTable.h
// This .h file contains the function prototypes for the handTable 

#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

#ifndef HANDTABLE_H
#define HANDTABLE_H

void loadHandTable(unordered_map<int, int> &flushes, unordered_map<int, int> &others);
int char_to_int(char cvalue); // convert char card value to int
int searchRank(int prime_multiple, bool flushesORnot, unordered_map<int, int> &flushes, unordered_map<int, int> &others);

#endif
