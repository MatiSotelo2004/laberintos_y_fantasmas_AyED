#include "laberinto.h"
void generarLaberinto(tTablero* laberinto)
{
    tpila historial;
    crearPila(&historial);

    generarEntradaLab(laberinto);
    tableroImprimir(laberinto,stdout,mostrarCharEnPantalla);
    puts("");
    generarSalidaLab(laberinto);
    tableroImprimir(laberinto,stdout,mostrarCharEnPantalla);
    puts("");
    inicializarInicioLab(laberinto);
    tableroImprimir(laberinto,stdout,mostrarCharEnPantalla);
    puts("");

    generarCaminoPrincipalLab(laberinto, &historial);
    tableroImprimir(laberinto,stdout,mostrarCharEnPantalla);
    puts("");
    limpiarEntradaLab(laberinto);
    limpiarSalidaLab(laberinto);

    agregarCaminosAleatoriosLab(laberinto, MAX_ALEATORIOS);

    destruirPila(&historial);
}

void generarEntradaLab(tTablero* laberinto)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(laberinto->limite.x));
    laberinto->entrada.x = columna;
    laberinto->entrada.y = BORDE_SUPERIOR;
    laberinto->tablero[BORDE_SUPERIOR][columna] = CARACTER_ENTRADA;
}

void generarSalidaLab(tTablero* laberinto)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(laberinto->limite.x));
    laberinto->salida.x = columna;
    laberinto->salida.y = BORDE_INFERIOR(laberinto->limite.y);
    laberinto->tablero[laberinto->salida.y][columna] = CARACTER_SALIDA;
}

void inicializarInicioLab(tTablero* laberinto)
{
    laberinto->actual.x = laberinto->salida.x - 1;
    laberinto->actual.y = laberinto->salida.y;
    laberinto->tablero[laberinto->actual.x][laberinto->actual.y] = LUGAR_VACIO;
}

void generarCaminoPrincipalLab(tTablero* laberinto, tpila* historial)
{
    tCoordenadas meta={laberinto->entrada.x,PRIMER_INTERIOR_FILA};
    int cont=0;
    while (!pilaVacia(historial) || laberinto->tablero[meta.x][meta.y]==LUGAR_VACIO)
    {
        calcularVecinosDisponiblesLab(laberinto);
        if (laberinto->vecinos.cantidad > 0)
        {
            apilarPila(historial, &laberinto->actual, sizeof(tCoordenadas));
            trazarCaminoHaciaVecinoLab(laberinto);
        }
        else
        {
            desapilarPila(historial, &laberinto->actual, sizeof(tCoordenadas));
        }
        tableroImprimir(laberinto,stdout,mostrarCharEnPantalla);
        puts("");
        cont++;
    }
        printf("Cantidad de iteraciones:%d\n",cont);
}

void trazarCaminoHaciaVecinoLab(tTablero* laberinto){
    tCoordenadas intermedio;
    tCoordenadas anterior = laberinto->actual;
    int eleccion = obtenerNumeroAleatorio(0, laberinto->vecinos.cantidad - 1);
    laberinto->actual = laberinto->vecinos.vecino[eleccion];
    intermedio = calcularCeldaIntermediaLab(&anterior,&laberinto->actual);
    laberinto->tablero[intermedio.x][intermedio.y] = LUGAR_VACIO;
    laberinto->tablero[laberinto->actual.x][laberinto->actual.y] = LUGAR_VACIO;
}

tCoordenadas calcularCeldaIntermediaLab(const tCoordenadas* origen, const tCoordenadas* destino)
{
    tCoordenadas intermedia;
    intermedia.x = (origen->x + destino->x) / 2;
    intermedia.y = (origen->y + destino->y) / 2;
    return intermedia;
}

void calcularVecinosDisponiblesLab(tTablero* laberinto)
{
    int desplazamientoX[MAX_DESPLAZAMIENTOS]={-SALTO_CELDA,SALTO_CELDA,0,0};
    int desplazamientoY[MAX_DESPLAZAMIENTOS]={0,0,-SALTO_CELDA,SALTO_CELDA};
    int filaVecina, columnaVecina;
    int cantidadVecinos = 0;
    for(int despla=0;despla< MAX_DESPLAZAMIENTOS;despla++)
    {
        filaVecina = laberinto->actual.x + desplazamientoX[despla];
        columnaVecina = laberinto->actual.y + desplazamientoY[despla];
        puts("");
        printf("FilaV:%d\nColuV:%d\n",filaVecina,columnaVecina);
        if (esVecinoValidoLab(laberinto, filaVecina, columnaVecina))
        {
            laberinto->vecinos.vecino[cantidadVecinos].x = filaVecina;
            laberinto->vecinos.vecino[cantidadVecinos].y = columnaVecina;
            cantidadVecinos++;
            puts("Vecino valido");
        }
        else{
            puts("Vecino no valido");
        }
    }
    puts("");
    printf("Vecinos:%d\n",cantidadVecinos);
    laberinto->vecinos.cantidad = cantidadVecinos;
}

int esVecinoValidoLab(const tTablero* laberinto, int fila, int columna){
    return fila > BORDE_SUPERIOR && fila < BORDE_INFERIOR(laberinto->limite.y) &&
           columna > BORDE_IZQUIERDO && columna < BORDE_DERECHO(laberinto->limite.x) &&
           laberinto->tablero[fila][columna] == CARACTER_PARED;
}

void limpiarEntradaLab(tTablero* lab)
{
    unsigned fil = lab->entrada.x + 1;
    unsigned col = lab->entrada.y;
    if (lab->tablero[fil][col] == CARACTER_PARED)
        lab->tablero[fil][col] = LUGAR_VACIO;
}


void limpiarSalidaLab(tTablero* lab)
{
    unsigned fil = lab->salida.x - 1;
    unsigned col = lab->salida.y;
    if (lab->tablero[fil][col] == CARACTER_PARED)
        lab->tablero[fil][col] = LUGAR_VACIO;
}

void agregarCaminosAleatoriosLab(tTablero* laberinto, int cantidadDeseada)
{
    const int FACTOR_INTENTOS_MAX = 50; // evita bucles infinitos
    const int MARGEN_BORDE = 2;         // evita tocar los bordes
    int caminosCreados = 0;
    int intentos = 0;
    int maxIntentos = cantidadDeseada * FACTOR_INTENTOS_MAX;

    int rangoFilas = (laberinto->limite.x - MARGEN_BORDE * 2) / 2;
    int rangoColumnas = (laberinto->limite.y - MARGEN_BORDE * 2) / 2;

    while (caminosCreados < cantidadDeseada && intentos < maxIntentos)
    {
        // Generar coordenadas aleatorias válidas (solo posiciones pares dentro del rango)
        int fila = obtenerNumeroAleatorio(0, rangoFilas - 1) * 2 + MARGEN_BORDE;
        int columna = obtenerNumeroAleatorio(0, rangoColumnas - 1) * 2 + MARGEN_BORDE;

        if (esPosicionValidaParaCaminoLab(laberinto, fila, columna))
        {
            laberinto->tablero[fila][columna] = LUGAR_VACIO;
            caminosCreados++;
        }

        intentos++;
    }
}

int esPosicionValidaParaCaminoLab(const tTablero* lab, int fila, int columna)
{
    // Evita abrir caminos sobre celdas ya vacías o bordes
    if (lab->tablero[fila][columna] != CARACTER_PARED)
        return 0;

    // Evita abrir justo al lado de la entrada o salida
    if ((fila == lab->entrada.x && columna == lab->entrada.y) ||
        (fila == lab->salida.x && columna == lab->salida.y))
        return 0;

    return 1;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}

