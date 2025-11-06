#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED


#include "../estructuras/tda_pila_dinamica.h"

#include "../coordenadas.h"

#define CARACTER_PARED '#'
#define CARACTER_INVALIDO '|'
#define LUGAR_VACIO '.'
#define CARACTER_JUGADOR 'J'
#define CARACTER_FANTASMA 'F'
#define CARACTER_VIDA 'V'
#define CARACTER_ENTRADA 'E'
#define CARACTER_SALIDA 'S'
#define CARACTER_PREMIO 'P'

#define VALOR_MINIMO 5
#define MAX_VECINOS 4
#define TABLERO_SIN_MEM -1
#define TABLERO_OK 0
#define POSICION_NO_DISPONIBLE -2
#define MOVIMIENTOS_SIN_MEMORIA NULL

typedef struct
{
    unsigned cantidad;
    tCoordenadas vecino[MAX_VECINOS];
}tVecinos;

typedef struct
{
    char **tablero;
    tCoordenadas limite;
    tCoordenadas entrada;
    tCoordenadas salida;
    tCoordenadas actual;
    tVecinos vecinos;
}tTablero;

int crearTablero(tTablero *tablero,tCoordenadas limites); ///VALIDADO

void tableroDibujarParedes(tTablero *tablero); ///VALIDADO VER
void tableroInicializar(tTablero *tablero, char caracter); ///VALIDADO VER

void destruirTablero(tTablero *tablero); ///VALIDADO
void imprimirTablero(const tTablero *tablero, FILE *pf); ///VALIDADO

void tableroColocarObjetosAleatorio(tTablero *tablero, unsigned cantObj, char caracter); ///VALIDADO VER
int colocarObjetoPosicionTablero(tTablero *tablero, const tCoordenadas *obj, char caracter); ///VALIDADO VER
void tableroColocarFantasmasAleatorio(tTablero *tablero,tCoordenadas* fantasmas, unsigned cantidadObjetos, char caracter);///VALIDADO VER



tCoordenadas* obtenerMovimientosTablero(const tTablero *tablero, const tCoordenadas *coords); ///VALIDADO VER


///FUNCIONES PARA CONSULTAR TABLERO
void obtenerObjetoPosicionTablero(const tTablero *tablero, const tCoordenadas *posicion, char *objeto);///VALIDADO
tCoordenadas obtenerLimiteTablero(const tTablero *tablero);///VALIDADO
tCoordenadas obtenerEntradaTablero(const tTablero *tablero);///VALIDADO
tCoordenadas obtenerSalidaTablero(const tTablero *tablero);///VALIDADO

int obtenerNumeroAleatorio(int minimo, int maximo);

#endif // TABLERO_H_INCLUDED
