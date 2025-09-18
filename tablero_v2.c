#include"tablero_v2.h"

int cargarConfig(tConfigTablero *config, const char *nomArch){
    FILE* fp = fopen(nomArch, "rt");

    if(!fp){
        return 1;
    }
    /*
    filas: 20
    columnas: 40
    vida_inicial: 2
    fantasmas: 4
    premios: 5
    vida_extra: 6
    */
    fscanf(fp, "filas: %d\n", &config->filas);
    fscanf(fp, "columnas: %d\n", &config->columnas);
    fscanf(fp, "vida_inicial: %d\n", &config->cantVidaInicial);
    fscanf(fp, "columnas: %d\n", &config->columnas);
    fscanf(fp, "fantasmas: %d\n", &config->cantFant);
    fscanf(fp, "premios: %d\n", &config->cantPremio);
    fscanf(fp, "vida_extra: %d\n", &config->cantVidaExtra);

    fclose(fp);
    return 0;
}


int inicializarTablero(tLaberinto *tab, tConfigTablero *config){

    int i=0;

    //RESERVA MEM PARA LAS COLUMNAS
    tab->mat = (char**)malloc(sizeof(char*) * (config->filas));
    if (!tab->mat){
        return 1;
    }

    //RESERVA MEM PARA LAS FILAS
    while(i < config->filas){
        tab->mat[i] = (char*)malloc(sizeof(char) * (config->columnas));
        if(!tab->mat[i]){
            for(int j=i-1; j>=0; j--){
                free(tab->mat[j]);
            }
            return 1;
        }
        i++;
    }

    //SE CARGA LA CONFIG
    tab->filasTotales=config->filas;
    tab->columnasTotales=config->columnas;

    return 0;
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
    tCordenadas coordHisto;
    tpila historial;

    llenarLabParedes(lab);
    crearPila(&historial);

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

    //lab->historial.tope = 0;

    cantidadVecinos(lab);

    while(!(pilaVacia(&historial))||(lab->vecinos.cantidad > 0))
    {
        if(lab->vecinos.cantidad > 0)
        {
            coordHisto.fila = lab->actual.fila;
            coordHisto.columna = lab->actual.columna;

            random = rand() %(lab->vecinos.cantidad);
            lab->actual.fila = lab->vecinos.vecino[random].fila;
            lab->actual.columna = lab->vecinos.vecino[random].columna;

            lab->mat[lab->actual.fila][lab->actual.columna] = CAMINO;
            lab->mat[(lab->actual.fila + coordHisto.fila) / 2 ][(lab->actual.columna + coordHisto.columna) / 2] = CAMINO;

            apilarPila(&historial, &coordHisto, sizeof(tCordenadas));
        }
        else
        {
            desapilarPila(&historial, &coordHisto, sizeof(tCordenadas));

            lab->actual.fila = coordHisto.fila;
            lab->actual.columna = coordHisto.columna;
        }
        cantidadVecinos(lab);
    }

    destruirPila(&historial);
    mostrarLab(lab);
}

void destruirTablero(tLaberinto*tab){
    for(int i=0; i < tab->filasTotales; i++){
        free(tab->mat[i]);
    }
    free(tab->mat);
}

