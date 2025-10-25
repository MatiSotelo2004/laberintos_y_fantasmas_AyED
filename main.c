#include "Comun.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{
    srand(time(NULL));
    SOCKET sockCliente;
    int servidorEncendido = iniciarServidor(&sockCliente);
    if(servidorEncendido == SERVIDOR_OFF)
        puts("JUGANDO EN MODO OFFLINE");

    tConfigTablero config;
    tTablero tablero;
    tPosObjeto objetos;
    tJugador jugador;
    char movimiento;
    char objetoEnPosicionSeleccionada;
    int i;
    tCola colaMovimientos;
    char nombre[MAX_TAM_NOMBRE_JUGADOR];
    crearCola(&colaMovimientos);

//    if(mostrarMenu()==FIN_JUEGO)
//        return 0;

    pedirString(MENSAJE_PEDIR_NOMBRE,nombre,MAX_TAM_NOMBRE_JUGADOR);
    configuracionTableroCargar(&config,"configs.txt");
    tableroCrear(&tablero,&config);
    tableroInicializar(&tablero, CARACTER_PARED);
    tableroDibujarParedes(&tablero);
    generarLab(&tablero);
    tCoordenadas coordenadaEntrada = tableroEntrada(&tablero);
    tCoordenadas coordenadaSalida =  tableroSalida(&tablero);
    tCoordenadas coordenadaFantasmaAux;
    tPortal portal;

    unsigned cantPremios = configuracionTableroObtenerCantidadPremios(&config);
    unsigned cantVidasInicial = configuracionTableroObtenerCantidadVidasInicial(&config);
    unsigned cantVidasExtra = configuracionTableroObtenerCantidadVidasExtra(&config);
    unsigned cantFantasmas = configuracionTableroObtenerCantidadFantasmas(&config);
    objetosCrear(&objetos,&config,&coordenadaEntrada);

    tableroColocarObjeto(&tablero,portalPunteroPuntoA(&portal),CARACTER_PORTAL);
    tableroColocarObjeto(&tablero,portalPunteroPuntoB(&portal),CARACTER_PORTAL);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos), cantPremios, CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos), cantVidasExtra, CARACTER_VIDA);
    tableroColocarObjetosAleatorio(&tablero, objetoFantasmasObtenerPunteroCoordenadas(&objetos,0), cantFantasmas, CARACTER_FANTASMA);

    if(crearPortalEnTablero(&portal,&tablero) != PORTAL_CREADO_EXITOSO)
        puts("AVISO: NO SE PUDO INICALIZAR PORTAL!");

    jugadorInicializar(&jugador,&coordenadaEntrada,cantVidasInicial,nombre);
    tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);

    tCoordenadas jugadorCoordsAux;
    tableroColocarObjeto(&tablero,&coordenadaEntrada,CARACTER_ENTRADA);
    while(!coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(&jugador)) && jugadorCantVidas(&jugador) > 0 && movimiento != '?')
    {
        jugadorCoordsAux = jugadorCoordenadas(&jugador);
        //la condicion de fin con el movimiento y el signo de pregunta es para que cuando hagamos pruebas "terminemos" el juego sin tener que llegar a la meta
        do
        {
            movimiento = jugadorPedirMovimiento();
        } while (movimiento != MOVIMIENTO_ABAJO && movimiento != MOVIMIENTO_ARRIBA
                && movimiento != MOVIMIENTO_IZQUIERDA && movimiento != MOVIMIENTO_DERECHA && movimiento != '?');

        coordenadaEjecutarMovimiento(&jugadorCoordsAux,movimiento);
        tableroVerObjeto(&tablero,&jugadorCoordsAux,&objetoEnPosicionSeleccionada);

        if(objetoEnPosicionSeleccionada != CARACTER_PARED)
        {
            ponerCola(&colaMovimientos,&jugadorCoordsAux,sizeof(tCoordenadas));

            if(objetoEnPosicionSeleccionada == CARACTER_PREMIO)
                jugadorSumarPuntaje(&jugador,CANT_PUNTAJE_POR_PREMIO_TABLERO);
            if(objetoEnPosicionSeleccionada == CARACTER_VIDA)
                jugadorSumarVida(&jugador);

            if(coordenadasSonIguales(jugadorCoordenadasPuntero(&jugador),&coordenadaEntrada))
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(&jugador),CARACTER_ENTRADA);
            else
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(&jugador),LUGAR_VACIO);


            for(i = 0; i < cantFantasmas; i++)
            {
                coordenadaFantasmaAux = objetoFantasmasObtenerCoordenadas(&objetos,i);
                coordenadaFantasmaAux = fantasmaObtenerSiguienteMovimiento(&tablero,&coordenadaFantasmaAux,&jugadorCoordsAux);
                ponerCola(&colaMovimientos,&coordenadaFantasmaAux,sizeof(tCoordenadas));
            }

            actualizarMovimientosTableroDesdeCola(&colaMovimientos,&tablero, &jugador,&objetos,&portal);
            tableroImprimir(&tablero,stdout,mostrarCharEnPantalla);
            puts("\n\n\n\n");
        }else
            coordenadasCopiar(jugadorCoordenadasPuntero(&jugador),&jugadorCoordsAux);
    }

    if(coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(&jugador)))
        jugadorSumarPuntaje(&jugador, CANT_PUNTAJE_POR_GANAR);


    vaciarCola(&colaMovimientos);
    tableroDestruir(&tablero);
    objetosDestruir(&objetos);
    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
