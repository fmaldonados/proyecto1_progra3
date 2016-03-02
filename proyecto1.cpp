#include<iostream>
#include<ncurses.h>
#include "pieza.h"

int main(int argc, char* argv[]){
	initscr();
	start_color();
	int width, height;

	pieza** tablero = new pieza* [8];
	for (int i = 0; i < 8; i++){
		tablero[i] = new pieza[8];
	}
		
	

	
	refresh();	
 	getch();		
	endwin();


	return 0;
}

