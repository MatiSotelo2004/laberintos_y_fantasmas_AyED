#include "Comun.h"

void pedirString(const char *mensaje, char *dest,unsigned tamMax)
{
    printf("%s",mensaje);
    fflush(stdin);
    char c;
    while ((c = getchar()) != '\n' && c != EOF); //limpia el buffer de entrada
    //intente hacer lo mismo con fflush(stdin) pero no funcionaba.
    fgets(dest,tamMax,stdin);

   while(*dest && *dest != '\n')
    dest++;

   if(*dest == '\n')
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

void convertirJugadorAJugadorDat(const tJugador *jug, tJugadorDat *jugDat)
{
    jugDat->cantMov = jug->cantMovimientos;
    jugDat->puntos += jug->puntaje;
    strcpy(jugDat->nombre,jug->nombre);
    jugDat->cantPartidas++;
}
