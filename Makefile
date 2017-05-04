# Makefile to run the game

CC=         g++
CFLAGS=     -c -std=c++11 -Wall
LD=         g++


all: play_game

play_game: play_game.o Game.o Round.o CardDeck.o handTable.o oddCalc.o AI.o
	$(LD) -o $@ $^

play_game.o: src/play_game.cpp
	$(CC) $(CFLAGS) -o $@ $^

Game.o: src/Game.cpp src/Game.h
	$(CC) $(CFLAGS) -o $@ $<

Round.o: src/Round.cpp src/Round.h src/CardDeck.h 
	$(CC) $(CFLAGS) -o $@ $<

CardDeck.o: src/CardDeck.cpp src/CardDeck.h
	$(CC) $(CFLAGS) -o $@ $<

handTable.o: src/handTable.cpp src/handTable.h
	$(CC) $(CFLAGS) -o $@ $<

oddCalc.o: src/oddCalc.cpp src/oddCalc.h
	$(CC) $(CFLAGS) -o $@ $<

AI.o: src/AI.cpp src/AI.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o play_game
