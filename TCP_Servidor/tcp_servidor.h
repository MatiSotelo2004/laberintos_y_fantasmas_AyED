#ifndef TCP_SERVIDOR_H_INCLUDED
#define TCP_SERVIDOR_H_INCLUDED

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "../macros.h"
#define SIN_MEMORIA_SERVIDOR -2
#define PORT 4040

typedef void (*Accion)(void *a, void *b);

int inicializarWinsock();
SOCKET crearSocketServer();
int servidorResponderCliente(SOCKET socketServidor, Accion funcion);

#endif // TCP_SERVIDOR_H_INCLUDED
