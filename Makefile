# This makefile test the Round class

test_round: test_round.cpp Round.o CardDeck.o
	g++ -std=c++11 -o $@ $^

Round.o: Round.cpp Round.h CardDeck.h
	g++ -c -std=c++11 -o $@ Round.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c -std=c++11 -o $@ CardDeck.cpp