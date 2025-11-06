#ifndef NUEVAPARTIDA_H_INCLUDED
#define NUEVAPARTIDA_H_INCLUDED

#include "estructuras/tda_cola_dinamica.h"

#include "juego/configuracion.h"
#include "juego/jugador.h"
#include "juego/tablero.h"
#include "juego/laberinto.h"
#include "juego/fantasmas.h"
#include "juego/portal.h"


#define MENSAJE_PEDIR_NOMBRE "Ingrese el nombre del jugador: "
#define MENSAJE_RECORDATORIO "Recuerde que los movimientos para desplazarce por el laberinto son 'a-w-s-d'"
#define MENSAJE_VICTORIA "Felicitaciones! Has escapado del laberinto con exito."
#define MENSAJE_DERROTA "No has podido completar el laberinto, te quedaste sin vidas!"
#define MENSAJE_MOTIVACION "La proxima sera un mejor intento!"
#define MENSAJE_AGRADECIMIENTO "Gracias por jugar!\n"

#define INFORME_JUGADOR "El jugador realizo los siguientes movimientos:"
#define INFORME_FANTASMA " - En el siguiente movimiento el jugador se encontro con un fantasma, por lo que vuelve a la entreda con una vida menos."
#define INFORME_PREMIO " - En el siguiente movimiento el jugador se encontro un premio, suma un punto."
#define INFORME_VIDA " - En el siguiente movimiento el jugador se encontro una vida, aumento su cantidad de vidas."
#define INFORME_SALIDA " - En el siguiente movimiento el jugador llego a la salida y gano el juego."
#define INFORME_PORTAL " - En el siguiente movimiento el jugador utilizo el portal, se teletransporto al otro lado."



#define CANT_PUNTAJE_POR_PREMIO_TABLERO 1
#define CANT_PUNTAJE_POR_GANAR 3
#define CARACTER_PORTAL 'O'
#define ERROR_PARTIDA -5

int jugarPartida(FILE* partida,tCola* movimientosJugador,tConfiguracion *configuracion, tJugador *jugador,const char *nomJugador);

tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posFantasma, const tCoordenadas *posJugador);
int crearPortalEnTablero(tPortal *portal, tTablero *tablero);


void ejecutarMovimientosTablero(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tFantasmas *fantasmas,int* cantFantasmas,const tPortal *portal);
void solicitarMovimiento(char *movimiento);
void eliminarFantasmaTablero(tTablero* tablero,tFantasmas* fantasma,int* cantFantasmas);

void mostrarRegistroJugador(tCola* registroJugador,FILE* partida);


#endif // NUEVAPARTIDA_H_INCLUDED
