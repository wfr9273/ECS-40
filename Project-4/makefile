CPU.out : decoder.o main.o  reader.o registers.o instruction.o labels.o
	g++ -g -Wall -ansi -o CPU.out decoder.o  main.o reader.o registers.o instruction.o labels.o 

decoder.o: decoder.cpp decoder.h registers.h reader.h instruction.h 
	g++ -g -Wall -ansi -c decoder.cpp

main.o: main.cpp registers.h decoder.h  reader.h instruction.h 
	g++ -g -Wall -ansi -c main.cpp

reader.o: reader.cpp reader.h registers.h 
	g++ -g -Wall -ansi -c reader.cpp

registers.o: registers.cpp registers.h 
	g++ -g -Wall -ansi -c registers.cpp

instruction.o: instruction.cpp instruction.h
	g++ -g -Wall -ansi -c instruction.cpp

labels.o: labels.cpp labels.h
	g++ -g -Wall -ansi -c labels.cpp
clean:
	rm -f CPU.out decoder.o  main.o  reader.o registers.o  instruction.o labels.o
