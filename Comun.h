#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#include "juego/jugador.h"
#include "cliente_LyF.h"

#define MAX_LINEA 1024
#define REGLAS_ERROR 1
#define REGLAS_OK 0
#define PARTIDA_ERROR 3
#define PARTIDA_OK 0
#define NOMBRE_ARCHIVO_HISTORIAL "jugadores.dat"
#define miToUpper(x) (((x)>='a')?((x)-('a'-'A')):(x))

int ingresarOpcion(const char *opcionesValidas);
void mostrarMenu(const char* titulo);
void pedirString(const char *mensaje, char *dest,unsigned tamMax);
void copiarNombreArchivo(void *a, void *b);
void seterHistorialJugador(void *a, void *b);
void convertirJugadorAJugadorDat(const tJugador *jug, tJugadorDat *jugDat);
int consultarReglas(const char* nombreArchivo);
int comenzarPartida(FILE** partida,const char* nombrePartida);

#endif // COMUN_H_INCLUDED
