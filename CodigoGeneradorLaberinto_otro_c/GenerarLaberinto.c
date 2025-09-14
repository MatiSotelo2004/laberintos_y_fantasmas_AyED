#include "GenerarLaberinto.h"

void crearLab(tLaberinto* lab)
{
    lab->filasTotales = FILASTOT;
    lab->columnasTotales = COLTOT;
}

void llenarLabParedes(tLaberinto* lab)
{
    int i,j;
    for(i = 0; i < lab->filasTotales; i++)
    {
        for(j = 0; j < lab->columnasTotales; j++)
        {
            lab->mat[i][j] = PARED;
        }
    }
}

void mostrarLab(tLaberinto* lab)
{
    int i,j;
    for(i = 0; i < lab->filasTotales; i++)
    {
        for(j = 0; j < lab->columnasTotales; j++)
        {
            printf("%c ",lab->mat[i][j]);
        }
        printf("\n");
    }
}

void cantidadVecinos(tLaberinto* lab)
{
    int dirFil[4] = {-2,2,0,0};
    int dirCol[4] = {0,0,-2,2};
    int i,fil,col,cant=0;

    for(i = 0; i < 4; i++)
    {
        fil = lab->actual.fila + dirFil[i];
        col = lab->actual.columna + dirCol[i];
        if(fil > 0 && fil < lab->filasTotales - 1 && col > 0 && col < lab->columnasTotales - 1 && lab->mat[fil][col] == PARED)
        {
            lab->vecinos.vecino[cant].fila = fil;
            lab->vecinos.vecino[cant].columna = col;
            cant++;
        }
    }
    lab->vecinos.cantidad = cant;
}

void generarLab(tLaberinto* lab)
{
    int random;

    crearLab(lab);
    llenarLabParedes(lab);

    srand(time(NULL));

    random = rand() % ((lab->columnasTotales + 1) / 2);
    lab->entrada.fila = 0;
    lab->entrada.columna = random * 2 + 1;
    lab->mat[lab->entrada.fila][lab->entrada.columna] = ENTRADA;

    random = rand() % ((lab->columnasTotales + 1) / 2);
    lab->salida.fila = lab->filasTotales - 1;
    lab->salida.columna = random * 2 + 1;
    lab->mat[lab->salida.fila][lab->salida.columna] = SALIDA;

    lab->actual.fila = lab->salida.fila - 1;
    lab->actual.columna = lab->salida.columna;
    lab->mat[lab->actual.fila][lab->actual.columna] = CAMINO;

    lab->historial.tope = 0;

    cantidadVecinos(lab);

    while((lab->historial.tope > 0)||(lab->vecinos.cantidad > 0))
    {
        if(lab->vecinos.cantidad > 0)
        {
            lab->historial.vec[lab->historial.tope].fila = lab->actual.fila;
            lab->historial.vec[lab->historial.tope].columna = lab->actual.columna;

            random = rand() %(lab->vecinos.cantidad);
            lab->actual.fila = lab->vecinos.vecino[random].fila;
            lab->actual.columna = lab->vecinos.vecino[random].columna;

            lab->mat[lab->actual.fila][lab->actual.columna] = CAMINO;
            lab->mat[(lab->actual.fila + lab->historial.vec[lab->historial.tope].fila) / 2 ][(lab->actual.columna + lab->historial.vec[lab->historial.tope].columna) / 2] = CAMINO;

            lab->historial.tope++;
        }
        else
        {
            lab->historial.tope--;

            lab->actual.fila = lab->historial.vec[lab->historial.tope].fila;
            lab->actual.columna = lab->historial.vec[lab->historial.tope].columna;
        }
        cantidadVecinos(lab);
    }

    mostrarLab(lab);
}
