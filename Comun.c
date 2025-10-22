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

void actualizarMovimientosTableroDesdeCola(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tPosObjeto *objetos)
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
        && objetoEnPosicion != CARACTER_FANTASMA)
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
