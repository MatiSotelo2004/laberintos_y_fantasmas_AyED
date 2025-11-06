#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int crearTablero(tTablero *tablero,tCoordenadas limites)
{
    int columnas = limites.x;
    int filas = limites.y;
    if(columnas < VALOR_MINIMO)
        columnas = VALOR_MINIMO;
    if(filas < VALOR_MINIMO)
        filas = VALOR_MINIMO;
    tablero->tablero=(char**)malloc(filas * sizeof(char*));
    if(!tablero->tablero)
        return TABLERO_SIN_MEM;
    for(int fil=0;fil<filas;fil++)
    {
        tablero->tablero[fil]=(char*)malloc(columnas * sizeof(char));
        if (!tablero->tablero[fil])
        {
            for (int elim=0;elim<fil;elim++)
                free(tablero->tablero[elim]);
            free(tablero->tablero);
            return TABLERO_SIN_MEM;
        }
    }
    tablero->limite.x=columnas;
    tablero->limite.y=filas;
    return TABLERO_OK;
}

void destruirTablero(tTablero *tablero)
{
    int filas=tablero->limite.y;
    for(int fil=0;fil<filas;fil++)
        free(tablero->tablero[fil]);
    free(tablero->tablero);
    tablero->tablero=NULL;
}

void imprimirTablero(const tTablero *tablero, FILE* pf)
{
    fprintf(pf,"   ");
    for(int col=0;col<tablero->limite.x;col++)
    {
    fprintf(pf,"%d",col%10);
    }
    fprintf(pf,"\n");
    for(int fil=0;fil<tablero->limite.y;fil++)
    {
        fprintf(pf,"%2d|",fil);
        for(int col=0;col<tablero->limite.x;col++)
        {
            fprintf(pf,"%c",tablero->tablero[fil][col]);
        }
        fprintf(pf,"\n");
    }
}
void tableroDibujarParedes(tTablero *tablero)
{
    int filas = tablero->limite.y;
    int columnas = tablero->limite.x;
    for(int col=0;col<columnas;col++)
    {
        tablero->tablero[0][col] = CARACTER_PARED;
        tablero->tablero[filas - 1][col] = CARACTER_PARED;
    }
    for(int fil=0;fil<filas;fil++)
    {
        tablero->tablero[fil][0] = CARACTER_PARED;
        tablero->tablero[fil][columnas - 1] = CARACTER_PARED;
    }
}

void tableroInicializar(tTablero *tablero, char caracter)
{
    for(int fil=1;fil<tablero->limite.y-1;fil++)
    {
        for(int col=1;col<tablero->limite.x-1;col++)
        {
            tablero->tablero[fil][col] = caracter;
        }
    }
}


void tableroColocarObjetosAleatorio(tTablero *tablero, unsigned cantidadObjetos, char caracter)
{
    tCoordenadas pos;
    for(int cant=0;cant<cantidadObjetos;cant++)
    {
        do
        {
            pos.y=obtenerNumeroAleatorio(1,tablero->limite.y-2);
            pos.x=obtenerNumeroAleatorio(1,tablero->limite.x-2);
        }
        while(tablero->tablero[pos.y][pos.x]!=LUGAR_VACIO);
        tablero->tablero[pos.y][pos.x] = caracter;
    }
}

void tableroColocarFantasmasAleatorio(tTablero *tablero,tCoordenadas* fantasmas, unsigned cantidadObjetos, char caracter)///VALIDADO MEJORAR?
{
    tCoordenadas* nroFantasma;
    tCoordenadas* ultFantasma=fantasmas+cantidadObjetos;
    for(nroFantasma=fantasmas;nroFantasma<ultFantasma;nroFantasma++)
    {

        do
        {
            nroFantasma->x=obtenerNumeroAleatorio(1,tablero->limite.x-2);
            nroFantasma->y=obtenerNumeroAleatorio(2,tablero->limite.y-2);
        }
        while(tablero->tablero[nroFantasma->y][nroFantasma->x]!=LUGAR_VACIO);
        tablero->tablero[nroFantasma->y][nroFantasma->x] = caracter;

    }
}

void obtenerObjetoPosicionTablero(const tTablero *tablero, const tCoordenadas *posicion, char *objeto)
{
    if(posicion->y>0 && posicion->x < tablero->limite.x && posicion->y < tablero->limite.y)
        *objeto = tablero->tablero[posicion->y][posicion->x];
    else
        *objeto = CARACTER_INVALIDO;
}

int colocarObjetoPosicionTablero(tTablero *tablero, const tCoordenadas *obj, char caracter)
{
    if(obj->x > tablero->limite.x || obj->y > tablero->limite.y)
        return POSICION_NO_DISPONIBLE;

    if(tablero->tablero[obj->y][obj->x] == CARACTER_PARED && caracter != CARACTER_ENTRADA && caracter != CARACTER_SALIDA)
        return POSICION_NO_DISPONIBLE;

    tablero->tablero[obj->y][obj->x] = caracter;
    return TODO_OK;
}






tCoordenadas* obtenerMovimientosTablero(const tTablero *tablero, const tCoordenadas *coords)
{
    tCoordenadas *disponibles;
    int actualX;
    int actualY;
    int cantMovimientosPosibles;
    tCoordenadas movimientosPosibles[] =
    {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
        {1,1},
        {-1,1},
        {1,-1},
        {-1,-1}
    };
    if (coords->x < 0 || coords->x >= tablero->limite.x || coords->y < 0 || coords->y >= tablero->limite.y)
        return NULL;
    cantMovimientosPosibles = sizeof(movimientosPosibles) / sizeof(tCoordenadas);
    disponibles = (tCoordenadas*)malloc(sizeof(tCoordenadas) * cantMovimientosPosibles);
    if(!disponibles)
        return MOVIMIENTOS_SIN_MEMORIA;

    for(int movimiento = 0; movimiento < cantMovimientosPosibles  ; movimiento++)
    {
        actualX = coords->x + movimientosPosibles[movimiento].x;
        actualY = coords->y + movimientosPosibles[movimiento].y;
        if(actualX > 0 && actualX < tablero->limite.x-1
        && actualY > 0 && actualY < tablero->limite.y-1
        && tablero->tablero[actualY][actualX] == LUGAR_VACIO)
        {
            (disponibles+movimiento)->x = actualX;
            (disponibles+movimiento)->y = actualY;
        }else
            (disponibles+movimiento)->x = (disponibles+movimiento)->y = POSICION_NO_DISPONIBLE;
    }

    return disponibles;
}


tCoordenadas obtenerLimiteTablero(const tTablero *tablero)
{
    return tablero->limite;
}

tCoordenadas obtenerEntradaTablero(const tTablero *tablero)
{
    return tablero->entrada;
}

tCoordenadas obtenerSalidaTablero(const tTablero *tablero)
{
    return tablero->salida;
}


int obtenerNumeroAleatorio(int minimo, int maximo)
{
    return rand() % (maximo - minimo + 1) + minimo;
}




