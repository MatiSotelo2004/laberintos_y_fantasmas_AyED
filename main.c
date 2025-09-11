#include "tablero.h"
#include "objetos.h"
#include "menu.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{

    /*
     *
     * PREGUNTAS
     1. La entrada puede ser de los laterales, o sólo del techo
     2. Preguntar por division de archivos .h y .c
     3. Cómo parsear el archivo de configs.txt (en qué forma vienen los datos)
     4. Es necesario validar los datos del archivo configs.txt // por ejemplo, el minimo tamaño de la matriz
     5.
     */
    srand(time(NULL));
    tConfigTablero config;
    tTablero tablero;
    tPosObjeto objetos;

    if(mostrarMenu()==FIN_JUEGO)
        return 0;

    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    //tableroInicializar(&tablero, '.');
    tableroDibujarParedes(&tablero);
    tCoordenadas coordenadaEntrada = tableroEstablecerEntrada(&tablero);
    tCoordenadas coordenadaSalida =  tableroEstablecerSalida(&tablero);
    objetosCrear(&objetos,&config,&coordenadaEntrada);

    //tableroColocarObjetosAleatorio(&tablero, objetoParedesObtenerPunteroCoordenadas(&objetos),configuracionTableroObtenerCantidadParedes(&config), CARACTER_PARED);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos),configuracionTableroObtenerCantidadPremios(&config), CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos),configuracionTableroObtenerCantidadVidas(&config), CARACTER_VIDA);

    tableroColocarObjeto(&tablero,&coordenadaEntrada,CARACTER_JUGADOR);

    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
