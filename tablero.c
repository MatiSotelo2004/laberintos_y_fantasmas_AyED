#include "tablero.h"
#include "coordenadas.h"
#include <stdlib.h>

<<<<<<< Updated upstream
tCoordenadas tableroSetearEntrada(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 1,posColumna);
    tablero->tablero[0][posColumna] = CARACTER_ENTRADA;
    tCoordenadas coordenada;
    coordenada.x = 0;
    coordenada.y = posColumna;
    return coordenada;
}

tCoordenadas tableroSetearSalida(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 1,posColumna);
    tablero->tablero[tablero->limite.x-1][posColumna] = CARACTER_SALIDA;
    tCoordenadas coordenada;
    coordenada.x = tablero->limite.x-1;
    coordenada.y = posColumna;
    return coordenada;
}

=======
>>>>>>> Stashed changes
int tableroCrear(tTablero *tablero, const tConfigTablero *config)
{
    char **i;
    char **j;
    char **fin;
    tablero->tablero = (char**)malloc(config->tamTablero.x * sizeof(char*));
    if(!tablero->tablero)
        return TABLERO_SIN_MEM;

    fin = tablero->tablero + config->tamTablero.x;
    for(i = tablero->tablero; i < fin; i++)
    {
        *i = (char*)malloc(config->tamTablero.y * sizeof(char));
        if(!*i)
        {
            for(j = i - 1; j >= tablero->tablero; j--)
                free(*j);

            free(tablero->tablero);
            return TABLERO_SIN_MEM;
        }
    }
    tablero->limite.x = config->tamTablero.x;
    tablero->limite.y = config->tamTablero.y;

    return TODO_OK;
}

void tableroDestruir(tTablero *tablero)
{
    char **i;
    char **fin = tablero->tablero + tablero->limite.x;
    for(i = tablero->tablero; i < fin; i++)
        free(*i);

    free(tablero->tablero);
}

void tableroDibujarParedes(tTablero *tablero)
{
    int i;
<<<<<<< Updated upstream
    for(i = 0; i < tablero->limite.x; i++)
=======
    for(i = 0; i < tablero->limite.x ; i++)
>>>>>>> Stashed changes
    {
        tablero->tablero[i][0] = CARACTER_PARED;
        tablero->tablero[i][tablero->limite.y-1] = CARACTER_PARED;
    }

    for(i = 0; i < tablero->limite.y ; i++)
    {
        tablero->tablero[0][i] = CARACTER_PARED;
        tablero->tablero[tablero->limite.x-1][i] = CARACTER_PARED;
    }
}

void tableroInicializar(tTablero *tablero, char caracter)
{
    int i,j;
    for(i = 1; i < tablero->limite.x - 1; i++)
    {
        for(j = 1 ; j < tablero->limite.y - 1; j++)
            tablero->tablero[i][j] = caracter;
    }
}

void tableroImprimir(const tTablero *tablero, FILE* fp, Accion mostrar)
{
    int i,j;
    for(i = 0; i < tablero->limite.x; i++)
    {
        for(j = 0; j < tablero->limite.y; j++)
            mostrar(fp,&tablero->tablero[i][j]);

        fprintf(fp,"\n");
    }
}

void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter)
{
    int i;
    tCoordenadas coordsAleatorias;
    for(i = 0; i < cantObj; i++)
    {
        OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
        OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        while(!POSICION_ESTA_DISPONIBLE(tablero->tablero,coordsAleatorias.x,coordsAleatorias.y))
        {
            OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
            OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        }

        tablero->tablero[coordsAleatorias.x][coordsAleatorias.y] = caracter;
        (coords + i)->x = coordsAleatorias.x;
        (coords + i)->y = coordsAleatorias.y;
    }
}

int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords)
{
    if(tablero->tablero[coords->x][coords->y] == LUGAR_VACIO)
        return 1;
    return 0;
}

void tableroVerObjeto(const tTablero *tablero, const tCoordenadas *coords, char *dest)
{
    if(coords->x < tablero->limite.x && coords->y < tablero->limite.y)
        *dest = tablero->tablero[coords->x][coords->y];
    else
        *dest = CARACTER_INVALIDO;

}

int tableroColocarObjeto(tTablero *tablero, const tCoordenadas *obj, char caracter)
{
    if(obj->x > tablero->limite.x || obj->y > tablero->limite.y)
        return POSICION_NO_DISPONIBLE;

    if(tablero->tablero[obj->x][obj->y] == CARACTER_PARED && caracter != CARACTER_ENTRADA && caracter != CARACTER_SALIDA)
        return POSICION_NO_DISPONIBLE;

    tablero->tablero[obj->x][obj->y] = caracter;
    return TODO_OK;
}

void cantidadVecinos(tTablero* lab)
{
    int dirFil[4] = {-2,2,0,0};
    int dirCol[4] = {0,0,-2,2};
    int i,fil,col,cant=0;

    for(i = 0; i < 4; i++)
    {
        fil = lab->actual.x + dirFil[i];
        col = lab->actual.y + dirCol[i];
        if(fil > 0 && fil < lab->limite.x - 1 && col > 0 && col < lab->limite.y - 1 && lab->tablero[fil][col] == CARACTER_PARED)
        {
            lab->vecinos.vecino[cant].x = fil;
            lab->vecinos.vecino[cant].y = col;
            cant++;
        }
    }
    lab->vecinos.cantidad = cant;
}

void generarLab(tTablero* lab)
{
    int random;
    tCoordenadas coordHisto;
    tpila historial;

    crearPila(&historial);

    srand(time(NULL));

    random = rand() % ((lab->limite.y + 1) / 2);
    lab->entrada.x = 0;
    lab->entrada.y = random * 2 + 1;
    lab->tablero[lab->entrada.x][lab->entrada.y] = CARACTER_ENTRADA;

    random = rand() % ((lab->limite.y + 1) / 2);
    lab->salida.x = lab->limite.x - 1;
    lab->salida.y = random * 2 + 1;
    lab->tablero[lab->salida.x][lab->salida.y] = CARACTER_SALIDA;

    lab->actual.x = lab->salida.x - 1;
    lab->actual.y = lab->salida.y;
    lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;

    //lab->historial.tope = 0;

    cantidadVecinos(lab);

    while(!(pilaVacia(&historial))||(lab->vecinos.cantidad > 0))
    {
        if(lab->vecinos.cantidad > 0)
        {
            coordHisto.x = lab->actual.x;
            coordHisto.y = lab->actual.y;

            random = rand() %(lab->vecinos.cantidad);
            lab->actual.x = lab->vecinos.vecino[random].x;
            lab->actual.y = lab->vecinos.vecino[random].y;

            lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;
            lab->tablero[(lab->actual.x + coordHisto.x) / 2 ][(lab->actual.y + coordHisto.y) / 2] = LUGAR_VACIO;

            apilarPila(&historial, &coordHisto, sizeof(tCoordenadas));
        }
        else
        {
            desapilarPila(&historial, &coordHisto, sizeof(tCoordenadas));

            lab->actual.x = coordHisto.x;
            lab->actual.y = coordHisto.y;
        }
        cantidadVecinos(lab);
    }

    //Limpiar entrada

    lab->actual.x = lab->entrada.x + 1;
    lab->actual.y = lab->entrada.y;
    if((lab->actual.y - 1 > 0) && (lab->tablero[lab->actual.x][lab->actual.y - 1] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x][lab->actual.y - 1] = LUGAR_VACIO;
    }
    if((lab->actual.y + 1 < lab->limite.y - 1) && (lab->tablero[lab->actual.x][lab->actual.y + 1] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x][lab->actual.y + 1] = LUGAR_VACIO;
    }
    if((lab->tablero[lab->actual.x + 1][lab->actual.y] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x + 1][lab->actual.y] = LUGAR_VACIO;
    }

    //Limpiar salida

    lab->actual.x = lab->salida.x - 1;
    lab->actual.y = lab->salida.y;
    if((lab->actual.y - 1 > 0) && (lab->tablero[lab->actual.x][lab->actual.y - 1] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x][lab->actual.y - 1] = LUGAR_VACIO;
    }
    if((lab->actual.y + 1 < lab->limite.y - 1) && (lab->tablero[lab->actual.x][lab->actual.y + 1] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x][lab->actual.y + 1] = LUGAR_VACIO;
    }
    if((lab->tablero[lab->actual.x - 1][lab->actual.y] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x - 1][lab->actual.y] = LUGAR_VACIO;
    }

   caminosRandom(lab);

    destruirPila(&historial);
}

void caminosRandom(tTablero* lab) //la cantidad de caminos esta con una macro en tablero.v2.h capas conviene cargarlos en archivo y preguntar ahi la cantidad de caminos random, capas abria un error si son tableros chicos con muchos caminos random
{ //capas conviene que la cantidad de caminos random se saque de una formula, ejemplo col*fil / 100 o algo asi
    int i=0,ran;
    while(i < CANTCAM)
    {
        ran = rand() % ((lab->limite.x - 2)/2) * 2 + 2;
        lab->actual.x = ran;
        ran = rand() % ((lab->limite.y - 2)/2) * 2 + 2;
        lab->actual.y = ran;
        if((((lab->tablero[lab->actual.x - 1][lab->actual.y] == LUGAR_VACIO) && (lab->tablero[lab->actual.x + 1][lab->actual.y] == LUGAR_VACIO) && (lab->tablero[lab->actual.x][lab->actual.y + 1] == CARACTER_PARED) && (lab->tablero[lab->actual.x][lab->actual.y - 1] == CARACTER_PARED))||((lab->tablero[lab->actual.x - 1][lab->actual.y] == CARACTER_PARED) && (lab->tablero[lab->actual.x + 1][lab->actual.y] == CARACTER_PARED) && (lab->tablero[lab->actual.x][lab->actual.y + 1] == LUGAR_VACIO) && (lab->tablero[lab->actual.x][lab->actual.y - 1] == LUGAR_VACIO)))&& lab->tablero[lab->actual.x][lab->actual.y] == CARACTER_PARED)
        {
//            printf("%d %d \n",lab->actual.x,lab->actual.y);
            lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;
            i++;
        }
    }
}

tCoordenadas tableroEntrada(const tTablero *tablero)
{
    return tablero->entrada;
}
tCoordenadas tableroSalida(const tTablero *tablero)
{
    return tablero->salida;
}
