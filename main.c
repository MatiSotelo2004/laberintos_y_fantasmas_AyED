#include "tablero.h"
#include "objetos.h"
#include "menu.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{
    srand(time(NULL));
    tConfigTablero config;
    tTablero tablero;
    tPosObjeto objetos;

    if(mostrarMenu()==FIN_JUEGO)
        return 0;
    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    tableroInicializar(&tablero, '.');
    tableroDibujarParedes(&tablero);
    tCoordenadas coordenadaEntrada = tableroEstablecerEntrada(&tablero);
    tCoordenadas coordenadaSalida =  tableroEstablecerSalida(&tablero);
    printf("Entrada: (%d , %d)\n",coordenadaEntrada.x,coordenadaEntrada.y);
    printf("Salida: (%d , %d)\n",coordenadaSalida.x,coordenadaSalida.y);


    objetosCrear(&objetos,&config);
    tableroColocarObjetosAleatorio(&tablero, objetoParedesObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadParedes(&config), CARACTER_PARED);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadPremios(&config), CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos),
                                   configuracionTableroObtenerCantidadVidas(&config), CARACTER_VIDA);

    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
