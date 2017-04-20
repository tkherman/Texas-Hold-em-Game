// test_round.cpp
// driver to test the round class

#include <iostream>
#include "Round.h"
#include "handTable.h"


int main() {
	unordered_map<int, int> flushes, others;
    loadHandData(flushes, others);
    Round r(3, flushes, others);
}
