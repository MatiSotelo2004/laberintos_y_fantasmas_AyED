#include "tablero.h"
#include "coordenadas.h"
#include <stdlib.h>

int tableroCrear(tTablero *tablero, const tConfigTablero *config)
{
    char **i;
    char **j;
    char **fin;
    int tamX = config->tamTablero.x;
    int tamY = config->tamTablero.y;

    // Forzar dimensiones impares
    if(tamX % 2 == 0) tamX++;
    if(tamY % 2 == 0) tamY++;

    // Validar tama�o minimo
    if(tamX < 5) tamX = 5;
    if(tamY < 5) tamY = 5;

    tablero->tablero = (char**)malloc(tamX * sizeof(char*));
    if(!tablero->tablero)
        return TABLERO_SIN_MEM;

    fin = tablero->tablero + tamX;
    for(i = tablero->tablero; i < fin; i++)
    {
        *i = (char*)malloc(tamY * sizeof(char));
        if(!*i)
        {
            for(j = i - 1; j >= tablero->tablero; j--)
                free(*j);

            free(tablero->tablero);
            return TABLERO_SIN_MEM;
        }
    }
    tablero->limite.x = tamX;
    tablero->limite.y = tamY;

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
    for(i = 0; i < tablero->limite.x ; i++)
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

    //srand(time(NULL));

    //ESTABLECE ENTRADA Y SALIDA
    random = 1 + rand() % lab->limite.y; //GENERA UN NUMERO ALEATORIO ENTRE 1 Y "LIMITE.Y"
    lab->entrada.x = 0;
    lab->entrada.y = random;
    lab->tablero[lab->entrada.x][lab->entrada.y] = CARACTER_ENTRADA;

    random = 1 + rand() % lab->limite.y; //GENERA UN NUMERO ALEATORIO ENTRE 1 Y "LIMITE.Y"
    lab->salida.x = lab->limite.x - 1;
    lab->salida.y = random;
    lab->tablero[lab->salida.x][lab->salida.y] = CARACTER_SALIDA;

    //SE SITUA EN LA SALIDA
    lab->actual.x = lab->salida.x - 1;
    lab->actual.y = lab->salida.y;
    lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;

    cantidadVecinos(lab);

    //BLUCLE PARA GENERAR EL CAMINO
    while(!(pilaVacia(&historial))||(lab->vecinos.cantidad > 0))
    {
        if(lab->vecinos.cantidad > 0)
        {
            coordHisto.x = lab->actual.x;
            coordHisto.y = lab->actual.y;

            random = rand() % (lab->vecinos.cantidad); // ELIGE ENTRE UNO DE LOS VECINOS
            lab->actual.x = lab->vecinos.vecino[random].x;
            lab->actual.y = lab->vecinos.vecino[random].y;

            //REEMPLAZA EL VECINO ELEGIDO POR UN LUGAR VACIO
            lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;
            lab->tablero[(lab->actual.x + coordHisto.x)>>1][(lab->actual.y + coordHisto.y)>>1] = LUGAR_VACIO;

            //SE APLILA LAS COORDENADAS PARA LLEVAR UN HISTORIAL
            apilarPila(&historial, &coordHisto, sizeof(tCoordenadas));
        }
        else
        {
            //EN CASO DE NO ENCONTRAR VECINOS RETROCEDE DESAPILANDO LAS COORDENADAS
            desapilarPila(&historial, &coordHisto, sizeof(tCoordenadas));

            lab->actual.x = coordHisto.x;
            lab->actual.y = coordHisto.y;
        }
        cantidadVecinos(lab);
    }

    //LIMPIA LA ENTRADA

    lab->actual.x = lab->entrada.x + 1;
    lab->actual.y = lab->entrada.y;
    if(lab->tablero[lab->actual.x][lab->actual.y] == CARACTER_PARED)
    {
        lab->tablero[lab->actual.x][lab->actual.y] = LUGAR_VACIO;
    }

    //LIMPIA LA SALIDA

    lab->actual.x = lab->salida.x - 1;
    lab->actual.y = lab->salida.y;
    if((lab->tablero[lab->actual.x][lab->actual.y] == CARACTER_PARED))
    {
        lab->tablero[lab->actual.x][lab->actual.y - 1] = LUGAR_VACIO;
    }


    caminosRandom(lab);

    destruirPila(&historial);
}


int esPosicionValidaParaCamino(const tTablero* lab, int x, int y)
{
    int conexionHorizontal = 0;
    int conexionVertical = 0;
    // VERIFICA SI ESTA DENTRO DE LOS LIMITES
    if(x < 2 || x >= lab->limite.x - 2) return 0;
    if(y < 2 || y >= lab->limite.y - 2) return 0;

    //VERIFICA QUE SEA UNA PARED
    if(lab->tablero[x][y] != CARACTER_PARED)
        return 0;

    // SE FIJA SI CONECTA DOS CAMINOS EXISTENTES
    // CONEXION HORIZONTAL (izquierda y derecha libres)
    if((lab->tablero[x - 1][y] == LUGAR_VACIO) &&
            (lab->tablero[x + 1][y] == LUGAR_VACIO) &&
            (lab->tablero[x][y - 1] == CARACTER_PARED) &&
            (lab->tablero[x][y + 1] == CARACTER_PARED))
        conexionHorizontal = 1;

    // CONEXION VERTICAL (arriba y abajo libres)
    if((lab->tablero[x][y - 1] == LUGAR_VACIO) &&
            (lab->tablero[x][y + 1] == LUGAR_VACIO) &&
            (lab->tablero[x - 1][y] == CARACTER_PARED) &&
            (lab->tablero[x + 1][y] == CARACTER_PARED))
        conexionVertical = 1;

    return conexionHorizontal || conexionVertical;
}

void caminosRandom(tTablero* lab)
{
    int x, y, rangoX, rangoY;
    //int cantidadCaminos = calcularCantidadCaminosRandom(lab);
    int cantidadCaminos = 40;
    int caminosCreados = 0;
    int intentos = 0;
    int maxIntentos = cantidadCaminos * 50;  // Evita bucle infinito

    while(caminosCreados < cantidadCaminos && intentos < maxIntentos)
    {

        rangoX = (lab->limite.x - 4) / 2;
        rangoY = (lab->limite.y - 4) / 2;

        x = (rand() % rangoX) * 2 + 2;
        y = (rand() % rangoY) * 2 + 2;

        if(esPosicionValidaParaCamino(lab, x, y))
        {
            lab->tablero[x][y] = LUGAR_VACIO;
            caminosCreados++;
        }

        intentos++;
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

tCoordenadas* tableroObtenerMovimientoPosible(const tTablero *tablero, const tCoordenadas *coords)
{
    tCoordenadas *disponible;

    if (coords->x < 0 || coords->x >= tablero->limite.x || coords->y < 0 || coords->y >= tablero->limite.y)
        return NULL;

    short int actualX;
    short int actualY;
    short int cantMovimientosPosibles;
    tCoordenadas desplazamientosPosibles[] =
    {
        {1,0},
        {-1,0},
        {0,1},
        {0,-1},
        {1,1},
        {-1,1},
        {1,-1},
        {-1,-1}
    };

    cantMovimientosPosibles = sizeof(desplazamientosPosibles) / sizeof(tCoordenadas);
    disponible = (tCoordenadas*)malloc(sizeof(tCoordenadas) * 8);
    if(!disponible)
        return NULL;

    for(int i = 0; i < cantMovimientosPosibles  ; i++)
    {
        actualX = coords->x + desplazamientosPosibles[i].x;
        actualY = coords->y + desplazamientosPosibles[i].y;

        if(actualX >= 0 && actualX < tablero->limite.x
        && actualY >= 0 && actualY < tablero->limite.y
        && tablero->tablero[actualX][actualY] == LUGAR_VACIO)
        {
            (disponible+i)->x = actualX;
            (disponible+i)->y = actualY;
        }else
            (disponible+i)->x = (disponible+i)->y = POSICION_NO_DISPONIBLE;
    }

    return disponible;
}
