#include "tcp_servidor.h"
#include "FuncionesServidor.h"
#include <string.h>

int main(int argc, char *argv[])
{

    if (inicializarWinsock() != 0)
    {
        printf("Error al inicializar Winsock\n");
        return 1;
    }

    SOCKET socketServer = crearSocketServer();
    if (socketServer == INVALID_SOCKET)
    {
        printf("Error al crear socket del servidor\n");
        WSACleanup();
        return 2;
    }

    printf("Servidor escuchando en puerto %d...\n", PORT);

    char opcion = *argv[1];

    if(opcion == OPCION_VER_HISTORIAL)
        servidorResponderCliente(socketServer, verHistorial);

    if(opcion == OPCION_NUEVO_JUGADOR)
        servidorResponderCliente(socketServer, archivoAgregarJugador);


    closesocket(socketServer);
    WSACleanup();
    return 0;
}

