#ifndef CLIENTE_LYF_H_INCLUDED
#define CLIENTE_LYF_H_INCLUDED
#include "macros.h"

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "colaDinamica.h"
#include "jugador.h"
#include "servidor/servidor_LyF.h"
#define SERVIDOR_OFF 25
#define SERVIDOR_ON 404
#define SERVIDOR_ERROR -2
#define EXISTE 1
#define NO_EXISTE 0
#define FORMATO_ENVIAR_DATOS_JUGADOR "%s,%d,%d,%d"

typedef void (*Accion)(void *a, void *b);

typedef struct
{
    char nombre[MAX_TAM_NOMBRE_JUGADOR];
    unsigned puntos;
    unsigned cantMov;
    unsigned cantPartidas;
} tHistorialJugador;

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define ERROR_ENVIANDO_DATOS -2
#define ERROR_RECIBIENDO_DATOS -3

int inicializarWinsock(void);
SOCKET conectarServer(const char *server_ip, int port);
// int enviarRecibirRespuesta(SOCKET sock, const char *nombreJugador, unsigned tamElem, void *datoRecibido);
void destruirWinsock(SOCKET sock);
int servidorBuscarNombre(SOCKET *sock, const char *nombre, tJugadorDat *destino);
int servidorDarAltaJugador(SOCKET *sock, const char *nombre, tJugadorDat *destino);
int servidorCargarNuevaPartida(SOCKET *sock, const tJugadorDat *jugador);
int iniciarServidor(SOCKET *sockCliente);
int servidorVerHistorialPartidas(SOCKET *sock);
int servidorInteractuar(SOCKET *sock, const char *peticion, char *respuestaServer, char *datosDevueltos);
void trozarDatosJugadorDat(char *linea, tJugadorDat *dest);

#endif // CLIENTE_LYF_H_INCLUDED
