#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "juego.h"
#include "comun.h"
#include "cliente_LyF.h"

#define ARCHIVO_CONFIGURACION "config.txt"
#define ARCHIVO_LABERINTO "laberinto.txt"
#define ARCHIVO_REGLAS "reglas.txt"

#define TITULO "BIENVENIDO A LABERINTOS Y FANTASMAS"

#define OPCION_VER_HISTORIAL 'A'
#define OPCION_NUEVA_PARTIDA 'B'
#define OPCION_REGLAS 'C'
#define OPCION_SALIR 'D'
#define OPCIONES_VALIDAS "ABCD"

int main()
{
    srand(time(NULL));
    char nombre[MAX_TAM_NOMBRE_JUGADOR];
    int servidor;
    int opcion;
    SOCKET sockCliente;
    tJugadorDat jugDat;
    tCola registroJugador;
    tConfiguracion config;
    tJugador jugador;
    FILE* partida;

    crearCola(&registroJugador);

    servidor = iniciarServidor(&sockCliente); ///REVISAR
    if(servidor == SERVIDOR_OFF){
        puts("AVISO -> JUGANDO EN MODO OFFLINE");
    }
    mostrarMenu(TITULO);
    opcion=ingresarOpcion(OPCIONES_VALIDAS);
    while(opcion != OPCION_SALIR)
    {
        switch(opcion)
        {
            case OPCION_VER_HISTORIAL:
                if(servidor == SERVIDOR_ON){
                    servidorVerHistorialPartidas(&sockCliente);
                }else{
                    puts("No se encuentra conectado el servidor.");
                }
                break;
            case OPCION_NUEVA_PARTIDA:
                if(comenzarPartida(&partida,ARCHIVO_LABERINTO)!=PARTIDA_OK){
                    puts("Error al comenzar la partida, no se pudo crear el archivo");
                    return PARTIDA_ERROR;
                }
                if(cargarConfiguracion(&config,ARCHIVO_CONFIGURACION) != CONFIGURACION_OK)
                {
                    puts("Error al cargar la configuracion del juego.");
                    return CONFIGURACION_ERROR;
                }
                pedirString(MENSAJE_PEDIR_NOMBRE,nombre,MAX_TAM_NOMBRE_JUGADOR);
                if(jugarPartida(partida,&registroJugador,&config,&jugador,nombre) == TODO_OK)
                {
                    if(servidor == SERVIDOR_ON)
                    {
                        if(servidorBuscarNombre(&sockCliente,nombre,&jugDat) == NO_EXISTE){
                            servidorDarAltaJugador(&sockCliente,nombre,&jugDat);
                        }
                        convertirJugadorAJugadorDat(&jugador,&jugDat);
                        servidorCargarNuevaPartida(&sockCliente,&jugDat);
                    }
                }
                else{
                    puts("Ocurrio un error en la partida.");
                }
                fclose(partida);
                system("cls");
                break;
            case OPCION_REGLAS:
                system("cls");
                consultarReglas(ARCHIVO_REGLAS);
                system("pause");
                system("cls");
                break;
        }
        mostrarMenu(TITULO);
        opcion=ingresarOpcion(OPCIONES_VALIDAS);
    }
    if(servidor == SERVIDOR_ON)
    {
        WSACleanup();
        closesocket(sockCliente);
    }
    puts("Gracias por jugar!!!");
    puts("Saliendo...");
    return 0;
}


