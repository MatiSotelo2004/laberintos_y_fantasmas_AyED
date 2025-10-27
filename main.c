#include "Comun.h"
#include "nuevaPartida.h"
int main()
{
    srand(time(NULL));
    SOCKET sockCliente;
    tJugadorDat jugDat;

    int servidorEncendido = iniciarServidor(&sockCliente);
     if(servidorEncendido == SERVIDOR_OFF)
         puts("AVISO -> JUGANDO EN MODO OFFLINE");

    int opMenu = mostrarMenu(_OPCIONES_VALIDAS);
    while(opMenu != OPCION_SALIR)
    {
        switch(opMenu)
        {
            case OPCION_VER_HISTORIAL:
                if(servidorEncendido == SERVIDOR_ON)
                    servidorVerHistorialPartidas(&sockCliente);
                break;

            case OPCION_NUEVA_PARTIDA:
                tConfigTablero config;
                tJugador jugador;
                char nombre[MAX_TAM_NOMBRE_JUGADOR];
                if(configuracionTableroCargar(&config,NOMBRE_ARCHIVO_CONFIGURACION) != TODO_OK)
                {
                    puts("Error al cargar informacion del tablero.");
                    return ARCHIVO_ERROR;
                }

                pedirString(MENSAJE_PEDIR_NOMBRE,nombre,MAX_TAM_NOMBRE_JUGADOR);

                if(nuevaPartida(&config,&jugador,nombre) == TODO_OK)
                {
                    if(servidorEncendido == SERVIDOR_ON)
                    {
                        if(servidorBuscarNombre(&sockCliente,nombre,&jugDat) == NO_EXISTE)
                            servidorDarAltaJugador(&sockCliente,nombre,&jugDat);

                        convertirJugadorAJugadorDat(&jugador,&jugDat);
                        servidorCargarNuevaPartida(&sockCliente,&jugDat);
                    }
                }
                else
                    puts("Ocurrio un error en la partida.");
                system("cls");
                break;
            case OPCION_SALIR:
                puts("Gracias por jugar!!!");
                puts("Saliendo...");
                break;
        }

        opMenu = mostrarMenu(_OPCIONES_VALIDAS);
    }

    if(servidorEncendido == SERVIDOR_ON)
    {
        WSACleanup();
        closesocket(sockCliente);
    }
    return 0;
}
