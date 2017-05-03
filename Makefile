#Makefile

all: play_game

play_game: play_game.o Game.o Round.o CardDeck.o handTable.o oddCalc.o AI.o
	g++ -std=c++11 -o $@ $^

play_game.o: play_game.cpp
	g++ -c -std=c++11 -o $@ $^

Game.o: Game.cpp Game.h
	g++ -c -std=c++11 -o $@ Game.cpp

Round.o: Round.cpp Round.h CardDeck.h 
	g++ -c -std=c++11 -o $@ Round.cpp

CardDeck.o: CardDeck.cpp CardDeck.h
	g++ -c -std=c++11 -o $@ CardDeck.cpp

handTable.o: handTable.cpp handTable.h
	g++ -c -std=c++11 -o $@ handTable.cpp

oddCalc.o: oddCalc.cpp oddCalc.h
	g++ -c -std=c++11 -o $@ oddCalc.cpp

AI.o: AI.cpp AI.h
	g++ -c -std=c++11 -o $@ AI.cpp

clean:
	rm -rf *.o play_game
