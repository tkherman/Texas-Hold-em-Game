// test_round.cpp
// driver to test the round class

#include <iostream>
#include <unordered_map>
#include "Round.h"
#include "handTable.h"


int main() {
	unordered_map<int, int> flushes, others;
    loadHandTable(flushes, others);
    Round r(5, flushes, others);
}
