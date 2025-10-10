#include "menu.h"
#include "Comun.h"

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
    int i;
    tCola colaMovimientos;

    crearCola(&colaMovimientos);

    //if(mostrarMenu()==FIN_JUEGO)
        //return 0;

    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    tableroInicializar(&tablero, CARACTER_PARED);
    tableroDibujarParedes(&tablero);
    generarLab(&tablero);
    tCoordenadas coordenadaEntrada = tableroEntrada(&tablero);
    tCoordenadas coordenadaSalida =  tableroSalida(&tablero);
    tCoordenadas coordenadaFantasmaAux;

    unsigned cantPremios = configuracionTableroObtenerCantidadPremios(&config);
    unsigned cantVidasInicial = configuracionTableroObtenerCantidadVidasInicial(&config);
    unsigned cantVidasExtra = configuracionTableroObtenerCantidadVidasExtra(&config);
    unsigned cantFantasmas = configuracionTableroObtenerCantidadFantasmas(&config);
    objetosCrear(&objetos,&config,&coordenadaEntrada);
    jugadorCrear(&jugador);

    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos), cantPremios, CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos), cantVidasExtra, CARACTER_VIDA);
    tableroColocarObjetosAleatorio(&tablero, objetoFantasmasObtenerPunteroCoordenadas(&objetos,0), cantFantasmas, CARACTER_FANTASMA);

    jugadorInicializar(&jugador,&coordenadaEntrada,cantVidasInicial);
    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);

    tCoordenadas jugadorCoordsAux = jugadorCoordenadas(&jugador);
    tableroColocarObjeto(&tablero,&coordenadaEntrada,CARACTER_ENTRADA);

    while(!coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(&jugador)) && jugadorCantVidas(&jugador) > 0 && movimiento != '?')
    {
        //la condicion de fin con el movimiento y el signo de pregunta es para que cuando hagamos pruebas "terminemos" el juego sin tener que llegar a la meta
        do
        {
            movimiento = jugadorPedirMovimiento();
        } while (movimiento != MOVIMIENTO_ABAJO && movimiento != MOVIMIENTO_ARRIBA
                && movimiento != MOVIMIENTO_IZQUIERDA && movimiento != MOVIMIENTO_DERECHA && movimiento != '?');

        coordenadaEjecutarMovimiento(&jugadorCoordsAux,movimiento);
        tableroVerObjeto(&tablero,&jugadorCoordsAux,&objetoEnPosicionSeleccionada);

        if(objetoEnPosicionSeleccionada != CARACTER_PARED) //&& objetoEnPosicionSeleccionada != CARACTER_INVALIDO)
        {
            if(objetoEnPosicionSeleccionada == CARACTER_PREMIO)
                jugadorSumarPuntaje(&jugador);
            if(objetoEnPosicionSeleccionada == CARACTER_VIDA)
                jugadorSumarVida(&jugador);

            if(coordenadasSonIguales(jugadorCoordenadasPuntero(&jugador),&coordenadaEntrada))
                tableroColocarObjeto(&tablero,&jugadorCoordsAux,CARACTER_ENTRADA);
            else
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(&jugador),LUGAR_VACIO);



            for(i = 0; i < cantFantasmas && !coordenadasSonIguales(&jugadorCoordsAux,objetoFantasmasObtenerPunteroCoordenadas(&objetos,i)); i++)
            {
                coordenadaFantasmaAux = objetoFantasmasObtenerCoordenadas(&objetos,i);
                coordenadaFantasmaAux = fantasmaObtenerSiguienteMovimiento(&tablero,&coordenadaFantasmaAux,&jugadorCoordsAux);

                tableroVerObjeto(&tablero,&coordenadaFantasmaAux,&objetoEnPosicionSeleccionada);
                if(objetoEnPosicionSeleccionada != CARACTER_PARED
                    && objetoEnPosicionSeleccionada != CARACTER_PREMIO
                    && objetoEnPosicionSeleccionada != CARACTER_VIDA
                    && objetoEnPosicionSeleccionada != CARACTER_FANTASMA)
                {
                    ponerCola(&colaMovimientos,&coordenadaFantasmaAux,sizeof(tCoordenadas));
                    tableroColocarObjeto(&tablero,objetoFantasmasObtenerPunteroCoordenadas(&objetos,i),LUGAR_VACIO);
                    // tableroColocarObjeto(&tablero,&coordenadaFantasmaAux,CARACTER_FANTASMA);
                    coordenadasCopiar(&coordenadaFantasmaAux,objetoFantasmasObtenerPunteroCoordenadas(&objetos,i));
                }

                if(coordenadasSonIguales(&jugadorCoordsAux,objetoFantasmasObtenerPunteroCoordenadas(&objetos,i)))
                {
                    jugadorRestarVida(&jugador);
                    coordenadasCopiar(&coordenadaEntrada,&jugadorCoordsAux);

                }
            }

            ponerCola(&colaMovimientos,&jugadorCoordsAux,sizeof(tCoordenadas));
            //tableroColocarObjeto(&tablero,&jugadorCoordsAux,CARACTER_JUGADOR);
            actualizarMovimientosTableroDesdeCola(&colaMovimientos,&tablero, &jugador);

            tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
            puts("\n\n\n\n");
        }else
            coordenadasCopiar(jugadorCoordenadasPuntero(&jugador),&jugadorCoordsAux);

    }

    vaciarCola(&colaMovimientos);
    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
