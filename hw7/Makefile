all: skyscraper


skyscraper: bst.h avlbst.h skyscraper.cpp Skyscraper.o 
	g++ -g -Wall $^ -o skyscraper

Skyscraper.o: Skyscraper.h Skyscraper.cpp
	g++ -g -Wall -c Skyscraper.cpp -o Skyscraper.o

clean:
	rm skyscraper
