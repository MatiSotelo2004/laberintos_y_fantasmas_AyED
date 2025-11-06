#include "comun.h"

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

int consultarReglas(const char* nombreArchivo){
    char linea[MAX_LINEA];
    FILE* pf=fopen(nombreArchivo,"rt");
    if(!pf){
        return REGLAS_ERROR;
    }
    while(fgets(linea,sizeof(linea),pf)){
        printf("%s",linea);
    }
    fclose(pf);
    return REGLAS_OK;
}

int ingresarOpcion(const char *opcionesValidas)
{
    char opcion;
    do
    {
        fflush(stdin);
        scanf("%c",&opcion);
        opcion = miToUpper(opcion);
    }while(!strchr(opcionesValidas,opcion));
    system("cls");
    return opcion;
}

void mostrarMenu(const char* titulo)
{
    printf("%s\n",titulo);
    puts("--------------------------------");
    puts("[A] Ver ranking de jugadores.");
    puts("[B] Jugar nueva partida.");
    puts("[C] Ver reglas del juego.");
    puts("[D] Salir del juego.");
    puts("--------------------------------");
    printf("Ingrese una opcion:");
}

int comenzarPartida(FILE** partida,const char* nombrePartida){
    *partida = fopen(nombrePartida,"wt");
    if(!(*partida)){
        return PARTIDA_ERROR;
    }
    return TODO_OK;
}

