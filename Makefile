#Makefile

all: test_game test_round

test_game: test_game.o Game.o Round.o CardDeck.o handTable.o oddCalc.o #AI_player.o
	g++ -std=c++11 -o $@ $^

test_game.o: test_game.cpp
	g++ -c -std=c++11 -o $@ $^

Game.o: Game.cpp Game.h
	g++ -c -std=c++11 -o $@ Game.cpp

test_round: test_round.o Round.o CardDeck.o handTable.o oddCalc.o
	g++ -std=c++11 -o $@ $^

test_round.o: test_round.cpp
	g++ -c -std=c++11 -o $@ $^

Round.o: Round.cpp Round.h CardDeck.h 
	g++ -c -std=c++11 -o $@ Round.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c -std=c++11 -o $@ CardDeck.cpp

handTable.o: handTable.cpp handTable.h
	g++ -c -std=c++11 -o $@ handTable.cpp

oddCalc.o: oddCalc.cpp oddCalc.h
	g++ -c -std=c++11 -o $@ oddCalc.cpp

#AI_player.o: AI_player.cpp AI_player.h
#    g++ -c -std=c++11 -o $@ AI_player.cpp

clean:
	rm -rf *.o test_round test_game
