#include "nuevaPartida.h"

int nuevaPartida(tConfigTablero *configTablero, tJugador *jugador,const char *nomJugador)
{
    srand(time(NULL));
    tPosObjeto objetos;
    tTablero tablero;
    tCoordenadas jugadorCoordsAux;
    char movimiento;
    char objetoEnPosicionSeleccionada;
    int i;
    tCola colaMovimientos;
    crearCola(&colaMovimientos);

    tableroCrear(&tablero,configTablero);
    tableroInicializar(&tablero, CARACTER_PARED);
    tableroDibujarParedes(&tablero);
    generarLab(&tablero);
    tCoordenadas coordenadaEntrada = tableroEntrada(&tablero);
    tCoordenadas coordenadaSalida = tableroSalida(&tablero);
    tCoordenadas coordenadaFantasmaAux;
    tPortal portal;

    unsigned cantPremios = configuracionTableroObtenerCantidadPremios(configTablero);
    unsigned cantVidasInicial = configuracionTableroObtenerCantidadVidasInicial(configTablero);
    unsigned cantVidasExtra = configuracionTableroObtenerCantidadVidasExtra(configTablero);
    unsigned cantFantasmas = configuracionTableroObtenerCantidadFantasmas(configTablero);
    objetosCrear(&objetos,configTablero,&coordenadaEntrada);
    tableroColocarObjetosAleatorio(&tablero, objetoPremioObtenerPunteroCoordenadas(&objetos), cantPremios, CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, objetoVidasObtenerPunteroCoordenadas(&objetos), cantVidasExtra, CARACTER_VIDA);
    tableroColocarObjetosAleatorio(&tablero, objetoFantasmasObtenerPunteroCoordenadas(&objetos,0), cantFantasmas, CARACTER_FANTASMA);

    if(crearPortalEnTablero(&portal,&tablero) != PORTAL_CREADO_EXITOSO)
    puts("AVISO: NO SE PUDO INICALIZAR PORTAL!");

    jugadorInicializar(jugador,&coordenadaEntrada,cantVidasInicial,nomJugador);
    tableroImprimir(&tablero,stdout,mostrarChar);

    tableroColocarObjeto(&tablero,&coordenadaEntrada,CARACTER_ENTRADA);
    while(!coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(jugador)) && jugadorCantVidas(jugador) > 0 && movimiento != '?')
    {
        jugadorCoordsAux = jugadorCoordenadas(jugador);
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
                jugadorSumarPuntaje(jugador,CANT_PUNTAJE_POR_PREMIO_TABLERO);
            if(objetoEnPosicionSeleccionada == CARACTER_VIDA)
                jugadorSumarVida(jugador);

            if(coordenadasSonIguales(jugadorCoordenadasPuntero(jugador),&coordenadaEntrada))
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(jugador),CARACTER_ENTRADA);
            else
                tableroColocarObjeto(&tablero,jugadorCoordenadasPuntero(jugador),LUGAR_VACIO);


            for(i = 0; i < cantFantasmas; i++)
            {
                coordenadaFantasmaAux = objetoFantasmasObtenerCoordenadas(&objetos,i);
                coordenadaFantasmaAux = fantasmaObtenerSiguienteMovimiento(&tablero,&coordenadaFantasmaAux,&jugadorCoordsAux);
                ponerCola(&colaMovimientos,&coordenadaFantasmaAux,sizeof(tCoordenadas));
            }

            actualizarMovimientosTableroDesdeCola(&colaMovimientos,&tablero, jugador,&objetos,&portal);
            system("cls");
            tableroImprimir(&tablero,stdout,mostrarChar);
        }else
            coordenadasCopiar(jugadorCoordenadasPuntero(jugador),&jugadorCoordsAux);
    }

    if(coordenadasSonIguales(&coordenadaSalida,jugadorCoordenadasPuntero(jugador)))
        jugadorSumarPuntaje(jugador, CANT_PUNTAJE_POR_GANAR);

    vaciarCola(&colaMovimientos);
    objetosDestruir(&objetos);
    tableroDestruir(&tablero);
    return 0;
}

void mostrarChar(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",*(char*)elem);
}

tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posFantasma, const tCoordenadas *posJugador)
{
    tCoordenadas* disponibles = tableroObtenerMovimientoPosible(tablero,posFantasma);
    tCoordenadas mejor;
    mejor.x = posFantasma->x;
    mejor.y = posFantasma->y;
    short int cantMovimientosFantasma = obtenerDistancia(posJugador,posFantasma) < 1.41 ? 4 : 8;

    for(int i = 0; i < cantMovimientosFantasma; i++) //8 es la maxima cantidad de movimientos disponibles para el fantasma.
        //si no queremos que el fantasma se mueva en diagonal, basta con reemplazar el 8 por un 4
    {
        if((disponibles+i)->x != COORDENADA_NO_DISPONIBLE && (disponibles+i)->y != COORDENADA_NO_DISPONIBLE)
        {
            if(obtenerDistancia(disponibles+i,posJugador) <= obtenerDistancia(&mejor,posJugador))
            {
                mejor.x = (disponibles+i)->x;
                mejor.y = (disponibles+i)->y;
            }
        }
    }

    free(disponibles);
    return mejor;
}

int crearPortalEnTablero(tPortal *portal, tTablero *tablero)
{
    char objetoEnEntradaDePortal;
    //sirve para verificar si la posicion de entrada al portal+1
    // es disponible
    char objetoEnSalidaPortal;//lo mismo con la salida

    tCoordenadas limiteTablero = tableroCoordenadasLimites(tablero);
    tCoordenadas entradaPortal;
    tCoordenadas salidaPortal;

    unsigned cantIntentos = limiteTablero.x;

    entradaPortal.y = 1;//en realidad va a estar en la columna cero la entrada,
    //pero la inicializo en 1 para ver que objeto hay al lado del portal

    OBTENER_NUM_ALEATORIO(1,limiteTablero.x,entradaPortal.x);
    //limite inferior, limite superior, destino donde voy a poner el numero aleatorio

    tableroVerObjeto(tablero,&entradaPortal,&objetoEnEntradaDePortal);

    while(cantIntentos && (objetoEnEntradaDePortal == CARACTER_PARED || objetoEnEntradaDePortal == CARACTER_FANTASMA))
    {
        OBTENER_NUM_ALEATORIO(1,limiteTablero.x,entradaPortal.x);
        tableroVerObjeto(tablero,&entradaPortal,&objetoEnEntradaDePortal);
        cantIntentos--;
    }

    if(cantIntentos == 0)
        return !PORTAL_CREADO_EXITOSO;

    cantIntentos = limiteTablero.x;
    salidaPortal.y = limiteTablero.y-2;

    OBTENER_NUM_ALEATORIO(1,limiteTablero.x,salidaPortal.x);
    tableroVerObjeto(tablero,&salidaPortal,&objetoEnSalidaPortal);

    while(cantIntentos && (objetoEnSalidaPortal == CARACTER_PARED || objetoEnSalidaPortal == CARACTER_FANTASMA))
    {
        OBTENER_NUM_ALEATORIO(1,limiteTablero.x,salidaPortal.x);
        tableroVerObjeto(tablero,&salidaPortal,&objetoEnSalidaPortal);
        cantIntentos--;
    }

    if(cantIntentos == 0)
        return !PORTAL_CREADO_EXITOSO;

    entradaPortal.y = 0;//lo dejo como deberia estar
    salidaPortal.y = limiteTablero.y-1;
    portalInicializar(portal,&entradaPortal,&salidaPortal);

    tableroColocarObjeto(tablero,&entradaPortal,portal->simbolo);
    tableroColocarObjeto(tablero,&salidaPortal,portal->simbolo);

    return PORTAL_CREADO_EXITOSO;
}

void actualizarMovimientosTableroDesdeCola(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tPosObjeto *objetos, const tPortal *portal)
{
    tCoordenadas jugadorCoords;
    tCoordenadas fantasmasCoords;
    tCoordenadas entradaTablero = tableroEntrada(tablero);
    sacarCola(colaMovimientos,&jugadorCoords,sizeof(tCoordenadas));
    unsigned posicionPunteroFantasmas = 0;
    char objetoEnPosicion;

    while(!colaVacia(colaMovimientos))
    {
        sacarCola(colaMovimientos,&fantasmasCoords,sizeof(tCoordenadas));
        tableroVerObjeto(tablero,&fantasmasCoords,&objetoEnPosicion);

        if(objetoEnPosicion != CARACTER_PARED
        && objetoEnPosicion != CARACTER_PREMIO
        && objetoEnPosicion != CARACTER_VIDA
        && objetoEnPosicion != CARACTER_FANTASMA
        && objetoEnPosicion != CARACTER_PORTAL)
        {
            tableroColocarObjeto(tablero,&fantasmasCoords,CARACTER_FANTASMA);
            tableroColocarObjeto(tablero,objetoFantasmasObtenerPunteroCoordenadas(objetos,posicionPunteroFantasmas),LUGAR_VACIO);
            coordenadasCopiar(&fantasmasCoords,objetoFantasmasObtenerPunteroCoordenadas(objetos,posicionPunteroFantasmas));
        }

        posicionPunteroFantasmas++;
    }

    tableroVerObjeto(tablero,&jugadorCoords,&objetoEnPosicion);

    if(objetoEnPosicion == CARACTER_FANTASMA)
    {
        jugadorRestarVida(jugador);
        coordenadasCopiar(&entradaTablero,&jugadorCoords);
    }else
        jugadorSumarCantidadDeMovimiento(jugador);

    if(objetoEnPosicion == CARACTER_PORTAL)
        portalTeletransportar(portal,&jugadorCoords);

    tableroColocarObjeto(tablero,&jugadorCoords,CARACTER_JUGADOR);
    jugadorMover(jugador,&jugadorCoords);
}
