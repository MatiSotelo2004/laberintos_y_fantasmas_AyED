#include <stdlib.h>
#define TODO_OK 0
#define TABLERO_SIN_MEM -1
#define ARCHIVO_ERROR -1
#define TAM_BUFFER 512
#define PARAMETRO_FILA_UBICACION 0
#define PARAMETRO_COLUMNA_UBICACION 1
#define PARAMETRO_VIDAS_INICIO_UBICACION 2
#define PARAMETRO_CANT_FANTASMAS_UBICACION 3
#define PARAMETRO_CANT_PREMIOS_UBICACION 4
#define PARAMETRO_CANT_VIDAS_EXTRA_UBICACION 5
#define ES_NUMERO(X) ((X) >= '0' && (X) <= '9')
#define OBTENER_NUM_ALEATORIO(MIN,MAX,DST) \
    ((DST) = (rand() % ((MAX) - (MIN))) + (MIN))
#define LUGAR_VACIO '.'
#define CARACTER_JUGADOR 'J'
#define CARACTER_FANTASMA 'F'
#define CARACTER_VIDA 'V'
#define CARACTER_ENTRADA 'E'
#define CARACTER_SALIDA 'S'
#define CARACTER_PREMIO 'P'
#define CARACTER_PARED '#'
#define CARACTER_INVALIDO '|'
#define MAX_CANT_PAREDES 50
#define POSICION_ESTA_DISPONIBLE(MATRIZ,FI,COL) ((MATRIZ[(FI)][(COL)]) == LUGAR_VACIO ? 1 : 0)
#define POSICION_NO_DISPONIBLE -2
#define MOVIMIENTO_ARRIBA 'w'
#define MOVIMIENTO_IZQUIERDA 'a'
#define MOVIMIENTO_ABAJO 's'
#define MOVIMIENTO_DERECHA 'd'
#define JUGADOR_ES_GANADOR 1
#define TITULO "BIENVENIDO A LABERINTOS Y FANTASMAS"
#define OPCION_A 'A' ///Ver raking de jugadores
#define OPCION_B 'B' ///Jugar nueva partida
#define OPCION_C 'C' ///Salir del juego
#define OPCION_D 'D' ///A definir si hacemos mas opciones de MENU_H_INCLUDED
#define miToUpper(x) (((x)>='a')?((x)-('a'-'A')):(x))
#define FIN_JUEGO 1
#define TODO_OK 0
