#ifndef HISTORIALPARTIDAS_H_INCLUDED
#define HISTORIALPARTIDAS_H_INCLUDED
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
}tHistorialJugador;


#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define ERROR_ENVIANDO_DATOS -2
#define ERROR_RECIBIENDO_DATOS -3
#define LLAMADA_A_SERVIDOR_VER_HISTORIAL "start \"TCP Server\" \"TCP_Servidor\\bin\\Debug\\TCP_Servidor.exe\" A" // la a es el argumento que recibe el programa
#define LLAMADA_A_SERVIDOR_AGREGAR_JUGADOR "start \"TCP Server\" \"TCP_Servidor\\bin\\Debug\\TCP_Servidor.exe\" D"// La d es el argumento que recibe el programa

int inicializarWinsock(void);
SOCKET conectarServer(const char *server_ip, int port);
//int enviarRecibirRespuesta(SOCKET sock, const char *nombreJugador, unsigned tamElem, void *datoRecibido);
void destruirWinsock(SOCKET sock);
void* servidorInteractuar(unsigned tamElemEnviar, unsigned tamElemRespuesta, const char *ejecutarLlamadaAlServidor, void *extra, Accion filtroSobreDatoAEnviar);
int iniciarServidor(SOCKET *sockCliente);
#endif // HISTORIALPARTIDAS_H_INCLUDED
