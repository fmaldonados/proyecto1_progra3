pieza:	pieza.o main.o
	g++ pieza.o main.o -lncurses
main.o:	proyecto1.cpp pieza.h
	g++ -c proyecto1.cpp -lncruses -o main.o 

pieza.o:	pieza.cpp pieza.h
	g++ -c pieza.cpp -o pieza.o
