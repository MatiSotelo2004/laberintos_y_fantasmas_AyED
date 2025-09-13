#include "tablero.h"
#include "objetos.h"
#include "menu.h"
#include "jugador.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{

    /*
     *
     * PREGUNTAS
     1. La entrada puede ser de los laterales, o sólo del techo --> CRITERIO NUESTRO
     2. Preguntar por division de archivos .h y .c --> ESTA BIEN QUE ESTE TODO DIVIDIDO
     3. Cómo parsear el archivo de configs.txt (en qué forma vienen los datos) --> DIJO QUE A CRITERIO NUESTRO
     4. Es necesario validar los datos del archivo configs.txt // por ejemplo, el minimo tamaño de la matriz
     5. Que pasa si un fantsama pasa por encima de un objeto? (VIDAEXTRA, PREMIO)? --> NO PUEDE PASAR POR ENCIMA DE UN OBJETO
     */
    srand(time(NULL));
    tConfigTablero config;
    tTablero tablero;
    tPosObjeto objetos;
    tJugador jugador;
    char movimiento;
    char objetoEnPosicionSeleccionada;

    //if(mostrarMenu()==FIN_JUEGO)
        //return 0;

    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    tableroInicializar(&tablero, LUGAR_VACIO);
    tableroDibujarParedes(&tablero);
    tCoordenadas coordenadaEntrada = tableroSetearEntrada(&tablero);
    tCoordenadas coordenadaSalida =  tableroSetearSalida(&tablero);
    tCoordenadas coordenadaFantasmaAux;
    unsigned cantParedes = configuracionTableroObtenerCantidadParedes(&config);
    unsigned cantPremios = configuracionTableroObtenerCantidadPremios(&config);
    unsigned cantVidasInicial = configuracionTableroObtenerCantidadVidasInicial(&config);
    unsigned cantVidasExtra = configuracionTableroObtenerCantidadVidasExtra(&config);
    unsigned cantFantasmas = configuracionTableroObtenerCantidadFantasmas(&config);
    objetosCrear(&objetos,&config,&coordenadaEntrada);
    jugadorCrear(&jugador);

    tableroColocarObjetosAleatorio(&tablero, objetoParedesObtenerPunteroCoordenadas(&objetos), cantParedes, CARACTER_PARED);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos), cantPremios, CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos), cantVidasExtra, CARACTER_VIDA);
    tableroColocarObjetosAleatorio(&tablero, objetoFantasmasObtenerPunteroCoordenadas(&objetos), cantFantasmas, CARACTER_FANTASMA);

    jugadorInicializar(&jugador,&coordenadaEntrada,cantVidasInicial);
    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);

    tCoordenadas jugadorCoordsAux = jugadorCoordenadas(&jugador);
    tableroColocarObjeto(&tablero,&coordenadaEntrada,CARACTER_ENTRADA);

    while(!coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(&jugador)) != 0 && cantVidasInicial != 0 && movimiento != '?')
    {
        //la condicion de fin con el movimiento y el signo de pregunta es para que cuando hagamos pruebas "terminemos" el juego sin tener que llegar a la meta
        do
        {
            movimiento = jugadorPedirMovimiento();
        } while (movimiento != MOVIMIENTO_ABAJO && movimiento != MOVIMIENTO_ARRIBA
                && movimiento != MOVIMIENTO_IZQUIERDA && movimiento != MOVIMIENTO_DERECHA && movimiento != '?');

        coordenadaEjecutarMovimiento(&jugadorCoordsAux,movimiento);
        tableroVerObjeto(&tablero,&jugadorCoordsAux,&objetoEnPosicionSeleccionada);

        if(objetoEnPosicionSeleccionada != CARACTER_PARED && objetoEnPosicionSeleccionada != CARACTER_INVALIDO)
        {
            if(coordenadasSonIguales(jugadorCoordenadasPuntero(&jugador),&coordenadaEntrada))
                tableroColocarObjeto(&tablero,&jugadorCoordsAux,CARACTER_ENTRADA);
            else
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(&jugador),LUGAR_VACIO);

            coordenadaFantasmaAux = objetoFantasmasObtenerCoordenadas(&objetos,0);//el 0 es cuál de todos los punteros de fantasma quiero

            coordenadasMovimientoRecomendado(&coordenadaFantasmaAux,jugadorCoordenadasPuntero(&jugador),
            &coordenadaFantasmaAux);

            tableroVerObjeto(&tablero,&coordenadaFantasmaAux,&objetoEnPosicionSeleccionada);
            if(objetoEnPosicionSeleccionada != CARACTER_PARED)
            {
                tableroColocarObjeto(&tablero,objetoFantasmasObtenerPunteroCoordenadas(&objetos),LUGAR_VACIO);
                tableroColocarObjeto(&tablero,&coordenadaFantasmaAux,CARACTER_FANTASMA);
                coordenadasCopiar(&coordenadaFantasmaAux,objetoFantasmasObtenerPunteroCoordenadas(&objetos));
            }

            tableroColocarObjeto(&tablero,&jugadorCoordsAux,CARACTER_JUGADOR);

            tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
            jugadorMover(&jugador,&jugadorCoordsAux);
            puts("\n\n\n\n");
        }else
            coordenadasCopiar(jugadorCoordenadasPuntero(&jugador),&jugadorCoordsAux);

    }

    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
