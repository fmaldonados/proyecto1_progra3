#include<iostream>
#include<ncurses.h>
#include "pieza.h"

void imprimirTablero(pieza***);
int convertir(int,char);
bool validar_piezas_seleccionadas(int,int,int,int,pieza***,int);
char identificar_pieza(pieza*);
bool puede_mover(char,int,int,int,int,int,pieza***);
bool puede_comer(char,int,int,int,int,int,pieza***);
char graduacion_peon(char[],int);
int main(int argc, char* argv[]){
	initscr();
	start_color();
	int width, height;
			
	pieza*** tablero = new pieza** [8];
	for (int i = 0; i < 8; i++){
		tablero[i] = new pieza*[8];
	}
	for(int i=0; i< 8;i++){
		for(int j=0; j<8;j++){
			tablero[i][j]=NULL;
		}
	}
	
	init_pair(1, COLOR_RED,     COLOR_BLACK);
    	init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    	init_pair(3, COLOR_CYAN,    COLOR_BLACK);
    	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    	init_pair(5, COLOR_WHITE,   COLOR_BLACK);

	getmaxyx(curscr,height,width);
	int move_this_y_1 = (height/2)-1;
	mvprintw(move_this_y_1,(width/3) -1,"Bienvenido al mejor juego de ajedrez del mundo!!!");
	getch();
	clear();
	attron(A_BOLD);
	bool terminar =false;
	while(!terminar){
		attron(COLOR_PAIR(4));
		mvprintw(move_this_y_1-1,(width/3) -1,".-*-.-*-.-*MENU.-*-.-*-.-*");
		attroff(COLOR_PAIR(4));
		attron(COLOR_PAIR(3));
		mvprintw(move_this_y_1,(width/3) -1,"1.-) Jugar");
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(1));
		mvprintw(move_this_y_1+2,(width/3) -1,"3.-) Salir.");
		attroff(COLOR_PAIR(1));

		attroff(A_BOLD);

		char opc = getch();
		clear();
		refresh();

		if(opc==49){
			char comidos_p1[]={'t','c','a','r','\0'},comidos_p2[]={'T','C','A','R','\0'};
			
			tablero[0][0]=new pieza('T',1,true);
        		tablero[0][1]=new pieza('C',1,true);
        		tablero[0][2]=new pieza('A',1,true);
        		tablero[0][3]=new pieza('Q',1,true);
        		tablero[0][4]=new pieza('K',1,true);
        		tablero[0][5]=new pieza('A',1,true);
        		tablero[0][6]=new pieza('C',1,true);
        		tablero[0][7]=new pieza('T',1,true);
        		for(int i=0; i<8;i++)
                		tablero[1][i]=new pieza('P',1,true);

        		tablero[7][0]=new pieza('t',2,true);
        		tablero[7][1]=new pieza('c',2,true);
        		tablero[7][2]=new pieza('a',2,true);
        		tablero[7][3]=new pieza('q',2,true);
        		tablero[7][4]=new pieza('k',2,true);
        		tablero[7][5]=new pieza('a',2,true);
        		tablero[7][6]=new pieza('c',2,true);
        		tablero[7][7]=new pieza('t',2,true);
        		for(int i=0; i<8;i++)
                		tablero[6][i]=new pieza('p',2,true);

			bool terminar_juego=false; //inicia el juego
			int bandera=1;
			while(!terminar_juego){
				imprimirTablero(tablero);
				attron(COLOR_PAIR(1));
				mvprintw((height/2-1)-8, (width/3 -1 )+2 ,"JUGADOR: ");
				attroff(COLOR_PAIR(1));
				attron(COLOR_PAIR(2));
				mvprintw((height/2-1)-8, (width/3 -1 )+10, "%i", bandera);
				attroff(COLOR_PAIR(2));

				attron(COLOR_PAIR(3));
				mvprintw(height-1, 0 ,"By: Felix Maldonado ");
				mvprintw((height/2-1)-6, (width/3 -1 )+2 ,"UTILIZAR SOLO MAYUSCULAS");
				mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"INGRESE EL COMANDO PARA MOVER: ");
				attroff(COLOR_PAIR(3));
				attron(COLOR_PAIR(2));
				char comando[5];
				int comando_cont = 0;	
				bool final_cadena = false;
				while(comando_cont < 4 && !final_cadena){
					noecho();
					char temp;//recibe un char de la entrada
					temp = getch();
					if(temp >= 65 && temp <= 72 && (comando_cont == 0 || comando_cont == 2 )){
						echo();
						addch(temp);
						comando[comando_cont] = temp;
						comando_cont++;
					}
					if(temp >= 49 && temp <= 56 && (comando_cont == 1 || comando_cont == 3 )){
                                        	echo();
                                        	addch(temp);
                                        	comando[comando_cont] = temp;
                                        	comando_cont++;
                                	}
					if(temp == 10 && comando_cont == 4){
						final_cadena = true;
						comando[comando_cont] = '\0';
					}
				}
				
				getch();
				attroff(COLOR_PAIR(2));
				int mover_x1,mover_y1, mover_x2, mover_y2;
			
				mover_x1 = convertir(mover_x1,comando[0]);
				mover_y1 = convertir(mover_y1,comando[1]);
				mover_x2 = convertir(mover_x2,comando[2]);
                        	mover_y2 = convertir(mover_y2,comando[3]);
				
			
				if(validar_piezas_seleccionadas(mover_x1,mover_y1,mover_x2,mover_y2,tablero,bandera)){
					char pieza_seleccionada = identificar_pieza(tablero[mover_y1][mover_x1]);
					if(tablero[mover_y2][mover_x2]==NULL){
						if(puede_mover(pieza_seleccionada,mover_x1,mover_y1,mover_x2, mover_y2,bandera,tablero)){
							tablero[mover_y2][mover_x2] = tablero[mover_y1][mover_x1];
							tablero[mover_y1][mover_x1]= NULL;	
							if(bandera==1){
								if(pieza_seleccionada=='p' && mover_y2==7){
									char convertir_peon ='\0';
									while(convertir_peon=='\0'){
										convertir_peon = graduacion_peon(comidos_p2,bandera);
										if(convertir_peon!='\0')
											tablero[mover_y2][mover_x2]->setTipo(convertir_peon);
										else{
						 					mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"No valido!");
											getch();
										}
									}
								}
							}else{
								if(pieza_seleccionada=='p' && mover_y2==0){
									char convertir_peon='\0';
                                                                        while(convertir_peon=='\0'){
                                                                                convertir_peon = graduacion_peon(comidos_p1,bandera);
                                                                                if(convertir_peon!='\0')
                                                                                        tablero[mover_y2][mover_x2]->setTipo(convertir_peon);
                                                                                else{
                                                                                        mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"No valido!");
											getch();
										}
                                                                        }
								}
							}
						}else{
						    mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"EL MOVIMIENTO NO ES VALIDO!!! INTENTA CON OTRO");
                                        		getch();
                                        		if(bandera==1)
                                                		bandera++;
                                       			else
                                                		bandera--;
							
						}
					}else{
						if(puede_comer(pieza_seleccionada,mover_x1,mover_y1,mover_x2, mover_y2,bandera,tablero)){
							if(bandera==1){
								tablero[mover_y2][mover_x2]->setJugador(bandera);
								tablero[mover_y2][mover_x2]->setTipo(tablero[mover_y1][mover_x1]->getTipo());
								tablero[mover_y1][mover_x1]=NULL;
								
								if(pieza_seleccionada=='p' && mover_y2==7){
									char convertir_peon='\0';
                                                                	while(convertir_peon =='\0'){
                                                                		convertir_peon = graduacion_peon(comidos_p2,bandera);
                                                                        	if(convertir_peon!='\0')
                                                                        		tablero[mover_y2][mover_x2]->setTipo(convertir_peon);
                                                                        	else{
                                                                                	mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"No valido!");
											getch();
										}
                                                                	}
								}
							}else{
								tablero[mover_y2][mover_x2]->setJugador(bandera);
                                                                tablero[mover_y2][mover_x2]->setTipo(tablero[mover_y1][mover_x1]->getTipo());
                                                                tablero[mover_y2][mover_x2]== tablero[mover_y1][mover_x1];
                                                                tablero[mover_y1][mover_x1]=NULL;
								
								if(pieza_seleccionada =='p' && mover_y2==0){
                                                                        char convertir_peon='\0';
                                                                        while(convertir_peon=='\0'){
                                                                                convertir_peon = graduacion_peon(comidos_p1,bandera);
                                                                                if(convertir_peon!='\0')
                                                                                        tablero[mover_y2][mover_x2]->setTipo(convertir_peon);
                                                                                else{
                                                                                        mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"No valido!");
											getch();
										}
                                                                        }
                                                                }

							}
							
						}else{
						    mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"EL MOVIMIENTO NO ES VALIDO!!! INTENTA CON OTRO");
                                                        getch();
                                                        if(bandera==1)
                                                                bandera++;
                                                        else
                                                                bandera--;

						}
					}	
				}else{
					mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"EL MOVIMIENTO NO ES VALIDO!!! INTENTA CON OTRO");
					getch();
					if(bandera==1)
                                        	bandera++;
                                	else
                                        	bandera--;
				}
				
				
				if(bandera==1)
					bandera++;
				else 
					bandera--;
				
				clear();
			}
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						delete [] tablero[i][j];
					}
				}

				for (int i = 0; i < 8; i++){
					delete[] tablero[i];
				}

				delete[] tablero;
				
				terminar=true;
							
		}else{
			if(opc==50){
				mvprintw(move_this_y_1-1,(width/3) -1,"GRACIAS POR UTILIZAR EL PROGRAMA TE ESPERAMOS PRONTO");
				terminar=true;
			}
			else
				mvprintw(move_this_y_1-1,(width/3) -1,"OPCION NO VALIDA!");
			
			clear();
			refresh();

		}
		
	}
	
 	getch();		
	endwin();
	
	

	return 0;
}
char graduacion_peon(char piezas_comidas[],int jugador){
	clear();
	int width, height;
        getmaxyx(curscr,height,width);
	char pieza_revivida = '\0';
	mvprintw((height/2-1)-1, (width/3 -1 )+2 , piezas_comidas);
	mvprintw((height/2-1)-4, (width/3 -1 )+2 ,"Ingrese la pieza que desea convertir su peon: ");

	char pieza_seleccionada=getch();
	if(jugador==1){
		if(pieza_seleccionada== 'p' || pieza_seleccionada=='P')
			pieza_revivida= 'P';
		else
			if(pieza_seleccionada== 'c'|| pieza_seleccionada=='C')
                        	pieza_revivida= 'C';
			else
				if(pieza_seleccionada== 'a' ||pieza_seleccionada=='A')
                        		pieza_revivida= 'A';
				else
					if(pieza_seleccionada== 'q' ||  pieza_seleccionada=='Q')
                        			pieza_revivida= 'Q';
					else
						if(pieza_seleccionada== 't'||  pieza_seleccionada=='T')
                        				pieza_revivida= 'T';
					
		 
		
	}else{
		if(pieza_seleccionada== 'p'  || pieza_seleccionada=='P')
                        pieza_revivida= 'p';
                else
                        if(pieza_seleccionada== 'C' || pieza_seleccionada=='c')
                                pieza_revivida= 'c';
                        else
                                if(pieza_seleccionada== 'A'|| pieza_seleccionada=='a')
                                        pieza_revivida= 'a';
                                else
                                        if(pieza_seleccionada=='Q' || pieza_seleccionada=='q')
                                                pieza_revivida= 'q';
                                        else
                                                if(pieza_seleccionada=='T' ||pieza_seleccionada=='t')
                                                        pieza_revivida= 't';
                                               


	}
	return pieza_revivida;
}
bool puede_comer(char actual ,int x1,int y1,int x2,int y2,int jugador,pieza*** tablero){
	bool si_puede=false;
	if(actual=='p'){
		if(jugador==1){
			if((x2==x1+1 && y2==y1+1) || (x2==x1-1 && y2==y1+1))
				si_puede=true;
		}else{
			if(x1==x2+1 && y1==y2+1 || x1==x2-1 && y1==y2+1)
                                si_puede=true;

		}
	}else{
		si_puede=puede_mover(actual,x1,y1,x2,y2,jugador,tablero) ;
	}
	return si_puede;
}
bool puede_mover(char actual ,int x1,int y1,int x2,int y2,int jugador,pieza*** tablero){
	bool si_puede=false;
	if(actual == 'p'){
		if(jugador == 1){
			bool primer_turno=false;
			if(x1==x2){
				int diferencia = y2-y1;
				if(y1==1){
					primer_turno=true;
				}
				
				if(diferencia == 1){
					si_puede=true;
				}else{
					if(diferencia == 2 && primer_turno){
						if(tablero[y1+1][x1]==NULL)
							si_puede=true;
						else
							si_puede=false;
					}else{
						si_puede=false;
					}
				}
				
			}else{
				si_puede= false;
			}
			
		}else{
			bool primer_turno=false;
                        if(x1==x2){
                                int diferencia= y1-y2;
                                if(y1==6){
                                        primer_turno=true;
                                }

                                if(diferencia==1){
                                        si_puede=true;
                                }else{
                                        if(diferencia==2 && primer_turno){
						if(tablero[y1-1][x1]==NULL)
                                                	si_puede=true;
						else
							si_puede=false;
                                        }else{
                                                si_puede=false;
                                        }
                                }

                        }else{
                                si_puede= false;
                        }

		
		}		

	}
	if(actual=='t'){
		int cont_piezas=0;
		if(x1==x2){
			int diferencia1=y1-y2;
			int diferencia2=y2-y1;
				
			if(diferencia1>0 && diferencia1<8){
				for(int i=y2-1; i>y1;i--){
					if(tablero[i][x1]!=NULL){
						cont_piezas++;
					}
				}
				if(cont_piezas==0)
					si_puede=true;
			}else{
				if(diferencia2>0 &&diferencia2<8){
					for(int i=y1+1; i<y2;i++){
                                                if(tablero[i][x1]!=NULL){
                                                	cont_piezas++;

                                                }
                                        }
					if(cont_piezas==0)
 	                                       si_puede=true;

	
				}else{
					si_puede=false;
				}
			}
		}else{
			if(y1==y2){
				int diferencia1=x1-x2;
                                int diferencia2=x2-x1;

                                if(diferencia1>0 && diferencia1<8){
                                        for(int i=x2-1; i>x1;i--){
                                                if(tablero[y1][i]!=NULL){
                                                         cont_piezas++;
                                                }
                                        }
					if(cont_piezas==0)
        	                                si_puede=true;
	
                                }else{
                                        if(diferencia2>0 &&diferencia2<8){
                                                for(int i=x1+1; i<x2;i++){
                                                        if(tablero[y1][i]!=NULL){
                                                                 cont_piezas++;
                                                        }
                                                }
						if(cont_piezas==0)
		                                        si_puede=true;

                                        }else{
                                                si_puede=false;
                                        }
                                }

			}else{
				si_puede=false;
			}
		}
	}
	if(actual == 'a'){
		int diferenciay1=y1-y2;
                int diferenciay2=y2-y1;
		int diferenciax1=x1-x2;
                int diferenciax2=x2-x1;
		if(diferenciay1==diferenciax1 || diferenciay1==diferenciax2 ||diferenciay2==diferenciax1 || diferenciay2==diferenciax2)
		if(diferenciay1>0 && diferenciay1<8){
			if(diferenciax1>0 && diferenciax1<8){
				int desplazamientox=x1-1,desplazamientoy=y1-1;
				si_puede=true;
				while(desplazamientox!=x2 && desplazamientoy!=y2){
					if(tablero[desplazamientoy][desplazamientox]!=NULL){
						si_puede=false;
						break;
					}
					desplazamientox--;
					desplazamientoy--;
				}
                	}else{
				if(diferenciax2>0 && diferenciax2<8){
					int desplazamientox=x2+1,desplazamientoy=y1-1;
					si_puede=true;
                                	while(desplazamientox!=x1 && desplazamientoy!=y2){
                                         	if(tablero[desplazamientoy][desplazamientox]!=NULL){
                                                	si_puede=false;
                                                	break;
                                        	}
                                        	desplazamientox++;
                                        	desplazamientoy--;
                                	}
                        	}else{
					si_puede=false;
				}
			}
		}else{
			if(diferenciay2>0 && diferenciay2<8){
				if(diferenciax1>0 && diferenciax1<8){
					int desplazamientox=x1-1,desplazamientoy=y1+1;
					si_puede=true;
                                	while(desplazamientox!=x2 && desplazamientoy!=y2){
                                        	if(tablero[desplazamientoy][desplazamientox]!=NULL){
                                                	si_puede=false;
                                                	break;
                                        	}
                                        	desplazamientox--;
                                        	desplazamientoy++;
                                	}
                        	}else{
					if(diferenciax2>0 && diferenciax2<8){
						int desplazamientox=x1+1,desplazamientoy=y1+1;
						si_puede=true;
                                		while(desplazamientox!=x2 && desplazamientoy!=y2){
                                        		if(tablero[desplazamientoy][desplazamientox]!=NULL){
                                                		si_puede=false;
                                        		}
                                        		desplazamientox++;
                                        		desplazamientoy++;
                                		}	
					}else{
						si_puede=false;
					}
				}
			}else{
				si_puede=false;
			}
		}
			
	}
	if (actual=='c'){
		if(y2==y1+2 && x2==x1+1){
			si_puede=true;
		}
		if(y2==y1-2 && x2==x1+1){
                        si_puede=true;
                }
		if(y2==y1+2 && x2==x1-1){
                        si_puede=true;
                }	
		if(y2==y1-2 && x2==x1-1){
                        si_puede=true;
                }
		if(y2==y1+1 && x2==x1+2){
                        si_puede=true;
                }
		if(y2==y1+1 && x2==x1-2){
                        si_puede=true;
                }
		if(y2==y1-1 && x2==x1+2){
                        si_puede=true;
                }
		if(y2==y1-1 && x2==x1-2){
                        si_puede=true;
                }
		
	}
	if(actual == 'q'){
		if(puede_mover('a',x1,y1,x2,y2,jugador,tablero) || puede_mover('t',x1,y1,x2,y2,jugador,tablero)){
			si_puede=true;
		}
	}
	if(actual == 'k'){
		if(x2==x1-1 && y2== y1-1){
			si_puede=true;
		}
		if(x2==x1-1 && y2== y1){
                        si_puede=true;
                }
		if(x2==x1-1 && y2== y1+1){
                        si_puede=true;
                }
		if(x2==x1 && y2== y1-1){
                        si_puede=true;
                }
		if(x2==x1 && y2== y1+1){
                        si_puede=true;
                }
		if(x2==x1+1 && y2== y1-1){
                        si_puede=true;
                }
		if(x2==x1+1 && y2== y1){
                        si_puede=true;
                }
		if(x2==x1+1 && y2== y1+1){
                        si_puede=true;
                }

	}
	return si_puede;
}
char identificar_pieza(pieza* pieza_selec){
	if(pieza_selec->getTipo() == 't' || pieza_selec->getTipo() == 'T'){
		return 't';
	}
	if(pieza_selec->getTipo() == 'c' || pieza_selec->getTipo() == 'C'){
        	return 'c';
        }
	if(pieza_selec->getTipo() == 'a' || pieza_selec->getTipo() == 'A'){
        	return 'a';		
        }
	if(pieza_selec->getTipo() == 'q' || pieza_selec->getTipo() == 'Q'){
        	return 'q';
        }
	if(pieza_selec->getTipo() == 'k' || pieza_selec->getTipo() == 'K'){
        	return 'k';
        }
	if(pieza_selec->getTipo() == 'p' || pieza_selec->getTipo() == 'P'){
        	return 'p';
        }
}
bool validar_piezas_seleccionadas(int x1,int y1,int x2,int y2,pieza*** tablero,int turno){
	bool todo_bien=true;
	
	if(tablero[y1][x1]!=NULL){
		if(tablero[y1][x1]->getJugador()!=turno){
			todo_bien=false;	
		}
	}else{
		todo_bien=false;
	}
	if(tablero[y2][x2]!=NULL){
		if(tablero[y2][x2]->getJugador()==turno){
			todo_bien=false;
                }
	}
	
	return todo_bien;
}

int convertir(int numero, char letra_convertir ){
	if(letra_convertir == 49 ){
		numero=0;
	}
	if(letra_convertir == 50 ){
                numero=1;
        }
	if(letra_convertir == 51 ){
                numero=2;
        }
	if(letra_convertir == 52 ){
                numero=3;
        }
	if(letra_convertir == 53 ){
                numero=4;
        }
	if(letra_convertir == 54 ){
                numero=5;
        }
	if(letra_convertir == 55 ){
                numero=6;
        }
	if(letra_convertir == 56 ){
                numero=7;
        }

	if(letra_convertir == 65 ){
                numero=0;
        }
	if(letra_convertir == 66 ){
                numero=1;
        }
 	if(letra_convertir == 67 ){
                numero=2;
        }
	if(letra_convertir == 68 ){
                numero=3;
        }
	if(letra_convertir == 69 ){
                numero=4;
        }
	if(letra_convertir == 70 ){
                numero=5;
        }
	if(letra_convertir == 71 ){
                numero=6;
        }
	if(letra_convertir == 72 ){
                numero=7;
        }



	return numero;
}
void imprimirTablero(pieza*** tablero){
	int width, height;
	getmaxyx(curscr,height,width);
	int cont2=0;
	mvprintw((height/2-1)-1, (width/3 -1 )+2 ," A    B    C    D    E    F    G    H");	
	for(int i=0; i< 8;i++){
		int cont=0;
		mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, "%i", i+1);
		cont++;
               for(int j=0; j<8;j++){
			if(tablero[i][j]!=NULL){
				mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, " ");
				cont++;
				mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, "[");
				cont++;
				char imprimir_pieza[] = {tablero[i][j]->getTipo(),'\0'};
                        	mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, imprimir_pieza);
				cont++;
				mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, "]");
				cont++;
				mvprintw((height/2-1)+cont2, (width/3 -1 ) + cont, " ");
				cont++;
			}else{
				mvprintw((height/2 -1) +cont2, (width/3-1)+cont," ");
				cont++;
				mvprintw((height/2 -1) +cont2, (width/3-1)+cont,"[");
				cont++;
				mvprintw((height/2 -1) +cont2, (width/3-1)+cont,"-");
				cont++;
				mvprintw((height/2 -1) +cont2, (width/3-1)+cont,"]");
				cont++;
				mvprintw((height/2 -1) +cont2, (width/3-1)+cont," ");
				cont++;
			}
               }
		cont2 +=2;
	}
}
