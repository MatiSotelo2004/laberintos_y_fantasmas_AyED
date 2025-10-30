#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TODO_OK 0
#define LISTA_VACIA 1
#define LISTA_LLENA 2
#define SIN_MEMORIA 3
#define MINLISTA(a,b) (((a)<(b))?(a):(b))
#define CON_DUPLICADO 0
#define SIN_DUPLICADO 1
#define ES_DUPLICADO 4
#define SI_ENCONTRO 0
#define NO_ENCONTRO 1
#define SIN_COINCIDENCIA 4
#define VACIO -1


typedef struct sNodoLista{
    void* info;
    unsigned tam;
    struct sNodoLista* sig;
    struct sNodoLista* ant;
}tNodoLista;

typedef tNodoLista* tLista;

typedef int Duplicado;
typedef void (*AccionLista)(const void* a);
typedef int (*Filtro)(const void* a);
typedef int (*Cmp)(const void* a,const void* b);
typedef void (*Act)(void*a,const void*b);

void crearLista(tLista* lista);
int insertarListaDetras(tLista* lista,const void* dato,unsigned tam);
int insertarListaDelante(tLista* lista,const void* dato,unsigned tam);
int insertarOrdenadoLista(tLista* lista,const void* dato,unsigned tam,Cmp cmp,Duplicado condicion,Act act);
int sacarActualLista(tLista* lista,void* dato,unsigned tam);
int sacarPrimeroLista(tLista* lista,void* dato,unsigned tam);
int sacarUltimoLista(tLista* lista,void* dato,unsigned tam);
int sacarPorClaveOrdenadoLista(tLista* lista,void* dato,unsigned tam,Cmp cmp);
int eliminarTodasLasCoincidenciasLista(tLista* lista,Filtro filtro);
void vaciarLista(tLista* lista);
int listaLlena(const tLista* lista,unsigned tam);
int listaVacia(const tLista* lista);
int verActual(const tLista* lista,void* dato,unsigned tam);
void recorrerListaIzqDer(const tLista* lista, AccionLista accion);
void recorrerListaDerIzq(const tLista* lista, AccionLista accion);
int buscarEnLista(const tLista* lista,void* dato,unsigned tam,Cmp cmp);
//int insertarPosicionLista(tLista* lista,const void* dato,unsigned tam,unsigned pos);
//tNodo** buscarMenor(tLista* lista,Cmp cmp);
//void ordenarLista(tLista* lista,Cmp cmp);



#endif // LISTADOBLE_H_INCLUDED
