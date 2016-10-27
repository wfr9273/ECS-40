CPU.out: main.o registers.o decoder.o reader.o instruction.h
	g++ -Wall -ansi -o CPU.out main.o decoder.o reader.o registers.o
main.o: main.c main.h registers.h decoder.h reader.h instruction.h
	g++ -Wall -ansi -c main.c
registers.o: registers.c registers.h main.h 
	g++ -Wall -ansi -c registers.c
decoder.o: decoder.c decoder.h registers.h
	g++ -Wall -ansi -c decoder.c
reader.o: reader.c reader.h instruction.h
	g++ -Wall -ansi -c reader.c

clean:
	rm -f CPU.out main.o registers.o decoder.o reader.o

