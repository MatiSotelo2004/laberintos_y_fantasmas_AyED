#ifndef SERVIDOR_LYF_H
#define SERVIDOR_LYF_H

#define PUERTO 12345
#define IPSERVER "172.0.0.1"
#define BUFFER_SIZE 1024

#define BUSCAR 2
#define ALTA 3

#define OP_BUSCAR "BUSCAR"
#define OP_ALTA "ALTA"

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "../colaDinamica.h"
#include "arbol.h"

typedef struct
{
    char nombre[50];
    unsigned offset;
} tIndice;

typedef struct{
    char nombre[50];
    int cantPartidas;
    int puntos;
    int cantMov;
}tJugadorDat;

// FUNCIONES WINSOCK
int init_winsock();
SOCKET crearServer();

// FUNCIONES ADICIONALES
int cargarIndices(tArbol *arbol, FILE *arch);
int cmpIndices(const void *x, const void *y);
int procesarPeticion(tCola *colaPeticiones, tArbol *arbolIndice, char *response, 
    FILE *JugadoresDat, FILE *archIndices);
unsigned buscarIndice(tArbol *arbolIndice, const char *nombre, unsigned *offsetIndice);

#endif // SERVIDOR_LYF_H