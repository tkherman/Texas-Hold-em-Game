# This makefile test the Round class

test_exec: test_round.o Round.o CardDeck.o handTable.o
	g++ -std=c++11 -o $@ $^

test_round.o: test_round.cpp
    g++ -c -std=c++11 -o $@ test_round.cpp

Round.o: Round.cpp Round.h CardDeck.h
	g++ -c -std=c++11 -o $@ Round.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c -std=c++11 -o $@ CardDeck.cpp

handTable.o: handTable.cpp handTable.h
    g++ -c -std=c++11 -o $@ handTable.cpp

clean:
	rm -rf *.o test_exec
