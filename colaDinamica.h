#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#define COLA_LLENA 1
#define COLA_VACIA 2
#define TODO_OK 0
#define SIN_MEMORIA 1
#define ERROR_COLA -2
#include "nodo.h"

typedef struct{
    tNodo* pri;
    tNodo* ult;
}tCola;

void crearCola(tCola* cola);
int ponerCola(tCola* cola,const void* dato,unsigned tam);
int sacarCola(tCola* cola,void* dato,unsigned tam);
void vaciarCola(tCola* cola);
int verPrimero(const tCola* cola,void* dato,unsigned tam);
int colaLlena(const tCola* cola,unsigned tam);
int colaVacia(const tCola* cola);


#endif // COLADINAMICA_H_INCLUDED
