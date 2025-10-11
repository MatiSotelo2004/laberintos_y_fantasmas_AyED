#include "laberinto.h"

void generarLaberinto(tTablero* tablero)
{
    tpila historial;
    crearPila(&historial);

    generarEntrada(tablero);
    generarSalida(tablero);
    inicializarInicio(tablero);

    generarCaminoPrincipal(tablero, &historial);
    limpiarEntrada(tablero);
    limpiarSalida(tablero);

    agregarCaminosAleatorios(tablero, 40);

    destruirPila(&historial);
}

void generarEntradaLab(tTablero* tablero)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(tablero->limite.x));
    tablero->entrada.x = BORDE_SUPERIOR;
    tablero->entrada.y = columna;
    tablero->tablero[BORDE_SUPERIOR][columna] = CARACTER_ENTRADA;
}

void generarSalidaLab(tTablero* tablero)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(tablero->limite.x));
    tablero->salida.x = BORDE_INFERIOR(tablero->limite.y);
    tablero->salida.y = columna;
    tablero->tablero[tablero->salida.x][columna] = CARACTER_SALIDA;
}

void inicializarInicioLab(tTablero* tablero)
{
    tablero->actual.x = tablero->salida.x - 1;
    tablero->actual.y = tablero->salida.y;
    tablero->tablero[tablero->actual.x][tablero->actual.y] = LUGAR_VACIO;
}

void generarCaminoPrincipalLab(tTablero* tablero, tpila* historial)
{
    calcularVecinosDisponibles(tablero);
    while (!pilaVacia(historial) || tablero->vecinos.cantidad > 0)
    {
        if (tablero->vecinos.cantidad > 0)
        {
            apilarPila(historial, &tablero->actual, sizeof(tCoordenadas));
            trazarCaminoHaciaVecinoLab(tablero);
        }
        else
        {
            desapilarPila(historial, &tablero->actual, sizeof(tCoordenadas));
        }
        calcularVecinosDisponibles(tablero);
    }
}

void trazarCaminoHaciaVecinoLab(tTablero* tablero){
    tCoordenadas intermedio;
    tCoordenadas anterior = tablero->actual;
    int eleccion = obtenerNumeroAleatorio(0, tablero->vecinos.cantidad - 1);
    tablero->actual = tablero->vecinos.vecino[eleccion];
    intermedio = calcularCeldaIntermedia(anterior,tablero->actual);
    tablero->tablero[intermedio.x][intermedio.y] = LUGAR_VACIO;
    tablero->tablero[tablero->actual.x][tablero->actual.y] = LUGAR_VACIO;
}

tCoordenadas calcularCeldaIntermediaLab(const tCoordenadas* origen, const tCoordenadas* destino)
{
    tCoordenadas intermedia;
    intermedia.x = (origen->x + destino->x) / 2;
    intermedia.y = (origen->y + destino->y) / 2;
    return intermedia;
}

void calcularVecinosDisponibles(tTablero* tablero)
{
    int desplazamientoX[MAX_DESPLAZAMIENTOS]={-SALTO_CELDA,SALTO_CELDA,0,0};
    int desplazamientoY[MAX_DESPLAZAMIENTOS]={0,0,-SALTO_CELDA,SALTO_CELDA};
    int filaVecina, columnaVecina;
    int cantidadVecinos = 0;
    for(int despla=0;despla< MAX_DESPLAZAMIENTOS;despla++)
    {
        filaVecina = tablero->actual.x + desplazamientoX[despla];
        columnaVecina = tablero->actual.y + desplazamientoY[despla];
        if (esVecinoValido(tablero, filaVecina, columnaVecina))
        {
            tablero->vecinos.vecino[cantidadVecinos].x = filaVecina;
            tablero->vecinos.vecino[cantidadVecinos].y = columnaVecina;
            cantidadVecinos++;
        }
    }

    tablero->vecinos.cantidad = cantidadVecinos;
}

int esVecinoValido(const tTablero* tablero, int fila, int columna){
    return fila > BORDE_SUPERIOR && fila < BORDE_INFERIOR(tablero->limite.y) &&
           columna > BORDE_IZQUIERDO && columna < BORDE_DERECHO(tablero->limite.x) &&
           tablero->tablero[fila][columna] == CARACTER_PARED;
}
