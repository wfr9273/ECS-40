FileFind.out: directory.o main.o list.h
	g++ -Wall -ansi -g -o FileFind.out directory.o main.o
	
directory.o: directory.cpp directory.h list.h
	g++ -Wall -ansi -g -c directory.cpp
	
main.o: main.cpp directory.h list.h
	g++ -Wall -ansi -g -c main.cpp

clean:
	rm -rf main.o directory.o FileFind.out
