all: Scrabble


Scrabble: Dictionary.o Bag.o Player.o Board.o Scrabble.cpp Game.o Tile.h
	g++ -g -Wall $^ -o Scrabble
Game.o: Game.h Game.cpp
	g++ -g -Wall -c Game.cpp -o Game.o
Bag.o: Bag.cpp Bag.h
	g++ -g -Wall -c Bag.cpp -o Bag.o
Player.o: Player.h Player.cpp
	g++ -g -Wall -c Player.cpp -o Player.o
Board.o: Board.cpp Board.h
	g++ -g -Wall -c Board.cpp -o Board.o
Dictionary.o: Dictionary.h Dictionary.cpp
	g++ -g -Wall -c Dictionary.cpp -o Dictionary.o
clean:
	rm Scrabble