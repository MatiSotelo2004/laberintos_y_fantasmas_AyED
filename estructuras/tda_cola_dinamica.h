#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED
#include "nodo.h"

#define COLA_VACIA 1
#define COLA_LLENA 2
#define ERROR_COLA -2

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
