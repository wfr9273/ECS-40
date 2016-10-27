CPU.out : decoder.o main.o registers.o instruction.o labels.o word.o data.o memory.o instruction2.o
	g++ -Wall -g -ansi -o CPU.out decoder.o  main.o registers.o instruction.o labels.o word.o data.o memory.o instruction2.o

decoder.o: decoder.cpp decoder.h registers.h instruction.h memory.h data.h
	g++ -Wall -g -ansi -c decoder.cpp

main.o: main.cpp registers.h decoder.h instruction.h labels.h memory.h data.h word.h instruction2.h
	g++ -Wall -g  -ansi -c main.cpp

registers.o: registers.cpp registers.h memory.h data.h labels.h
	g++ -Wall -g  -ansi -c registers.cpp

instruction.o: instruction.cpp instruction.h word.h
	g++ -Wall -g -ansi -c instruction.cpp

labels.o: labels.cpp labels.h instruction2.h
	g++ -Wall -g -ansi -c labels.cpp

word.o: word.cpp word.h
	g++ -Wall -g -ansi -c word.cpp

data.o: data.cpp data.h word.h
	g++ -Wall -g  -ansi -c data.cpp

memory.o: memory.cpp memory.h word.h data.h registers.h instruction.h
	g++ -Wall -g -ansi -c memory.cpp

instruction2.o: instruction2.cpp instruction2.h
	g++ -Wall -g -ansi -c instruction2.cpp

clean:
	rm -f CPU.out decoder.o  main.o registers.o  instruction.o labels.o word.o data.o memory.o instruction2.o
