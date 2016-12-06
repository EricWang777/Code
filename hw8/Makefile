all: counting


counting: counting.cpp Hashtable.o
	g++ -g -Wall $^ -o counting

Hashtable.o: Hashtable.h Hashtable.cpp
	g++ -g -Wall -c Hashtable.cpp -o Hashtable.o

clean:
	rm counting
