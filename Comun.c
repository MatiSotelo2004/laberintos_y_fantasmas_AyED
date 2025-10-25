#include "Comun.h"

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

void pedirString(const char *mensaje, char *dest,unsigned tamMax)
{
    printf("%s",mensaje);
    char c;
    while ((c = getchar()) != '\n' && c != EOF); //limpia el buffer de entrada
    //intente hacer lo mismo con fflush(stdin) pero no funcionaba.
    fgets(dest,tamMax,stdin);

    if(*dest && strlen(dest) > 1 && *(dest+strlen(dest-1)) == '\n')
        *dest = '\0';
}

void copiarNombreArchivo(void *a, void *b)
{
    strcpy((char*)a,NOMBRE_ARCHIVO_HISTORIAL);
}

void seterHistorialJugador(void *a, void *b)
{
    tHistorialJugador *historial = (tHistorialJugador*)a;
    const tJugador *jug = (const tJugador*)b;

    strcpy(historial->nombre,jug->nombre);
    historial->cantMov = jug->cantMovimientos;
    historial->puntos = jug->puntaje;
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
