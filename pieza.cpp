#include "pieza.h"
#include <iostream>

pieza::pieza(){
}

pieza::pieza(char tipo, int jugador, bool vive){
	this -> tipo =tipo;
	this -> jugador = jugador;
	this -> vive = vive;
}

void pieza::setTipo(char tipo){
	this -> tipo = tipo;
}

void pieza::setJugador(int jugador){
        this -> tipo = jugador;
}

void pieza::setVive(bool vive){
        this -> vive = vive;
}

char pieza::getTipo(){
	return tipo;
}

int pieza::getJugador(){
	return jugador;
}
bool pieza::getVive(){
	return vive;
}
