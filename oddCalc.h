// oddCalc.h
// file that includes functions for calculating odds

#include <vector>
#include <unordered_map>
#include "CardDeck.h"
using namespace std;

#ifndef ODDCALC_H
#define ODDCALC_H

int determine_best_rank(Card[2], vector<Card>, unordered_map<int, int>&,
    unordered_map<int, int> &);

int monteCarlo(CardDeck, Card[2], vector<Card>, unordered_map<int, int>&,
    unordered_map<int, int> &);

double getOdds(Card[2], vector<Card>, unordered_map<int, int>&,
    unordered_map<int, int>&, int);

#endif

