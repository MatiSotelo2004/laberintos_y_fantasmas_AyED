#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "stdlib.h"
#include "stdio.h"
#define TITULO "BIENVENIDO A LABERINTOS Y FANTASMAS"
#define OPCION_A 'A' ///Ver raking de jugadores
#define OPCION_B 'B' ///Jugar nueva partida
#define OPCION_C 'C' ///Salir del juego
#define OPCION_D 'D' ///A definir si hacemos mas opciones de MENU_H_INCLUDED
#define miToUpper(x) (((x)>='a')?((x)-('a'-'A')):(x))
#define FIN_JUEGO 1
#define TODO_OK 0

int mostrarMenu();
void printOpciones();


#endif // MENU_H_INCLUDED
