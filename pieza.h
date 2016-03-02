#ifndef PIEZA_H
#define PIEZA_H

class pieza{
	char tipo;
	int jugador;
	bool vive;
	public:
		pieza();
		pieza(char,int,bool);
		void setTipo(char);
		void setJugador(int);
		void setVive(bool);
		char getTipo();
		int getJugador();
		bool getVive();
};
#endif
