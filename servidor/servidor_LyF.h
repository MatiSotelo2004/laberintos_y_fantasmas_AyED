#ifndef SERVIDOR_LYF_H
#define SERVIDOR_LYF_H

#define PUERTO 12345
#define IPSERVER "172.0.0.1"
#define BUFFER_SIZE 1024

#define BUSCAR 2
#define ALTA 3

#define OP_BUSCAR 10
#define OP_ALTA 11
#define OP_GUARDAR 12
#define OP_HISTORIAL 13

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "../colaDinamica.h"
#include "arbol.h"
#include <windows.h>

typedef struct
{
    char nombre[50];
    unsigned offset;
} tIndice;

typedef struct
{
    char nombre[50];
    int cantPartidas;
    int puntos;
    int cantMov;
} tJugadorDat;

// FUNCIONES WINSOCK
int init_winsock();
SOCKET crearServer();

// FUNCIONES ADICIONALES
int cargarIndices(tArbol *arbol, FILE *arch);
int cmpIndices(const void *x, const void *y);
int procesarPeticion(tCola *colaPeticiones, tArbol *arbolIndice, char *response,
                     FILE *JugadoresDat, FILE *archIndices, SOCKET sockCliente);
void mostrarArchivo(FILE *fp);
int obtenerOpcion(const char *operacion);
void trozarDatosJugador(char *linea, tJugadorDat *dest);
#endif // SERVIDOR_LYF_H
