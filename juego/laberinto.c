#include "laberinto.h"

void generarLaberinto(tTablero* laberinto)
{
    tpila historial;
    tLista futurosCaminos;
    crearPila(&historial);
    crearLista(&futurosCaminos);
    generarEntradaLab(laberinto);
    generarSalidaLab(laberinto);
    posicionarActualEnSalidaLab(laberinto);
    generarCaminoPrincipalLab(laberinto, &historial,&futurosCaminos);
//    imprimirTablero(laberinto,stdout);
    generarCaminosExtrasLab(laberinto,&futurosCaminos);
//    imprimirTablero(laberinto,stdout);
    generarAberturasDeCaminosLab(laberinto);
//    imprimirTablero(laberinto,stdout);
    destruirPila(&historial);
    vaciarLista(&futurosCaminos);
}

void generarEntradaLab(tTablero* laberinto)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(laberinto->limite.x));
    int bordeSuperior = BORDE_SUPERIOR;
    laberinto->entrada.x = columna;
    laberinto->entrada.y = bordeSuperior;
    laberinto->tablero[bordeSuperior][columna] = CARACTER_ENTRADA;
}

void generarSalidaLab(tTablero* laberinto)
{
    int columna = obtenerNumeroAleatorio(PRIMER_INTERIOR_COL, ULTIMO_INTERIOR_COL(laberinto->limite.x));
    int bordeInferior=BORDE_INFERIOR(laberinto->limite.y);
    laberinto->salida.x = columna;
    laberinto->salida.y = bordeInferior;
    laberinto->tablero[bordeInferior][columna] = CARACTER_SALIDA;
}

void posicionarActualEnSalidaLab(tTablero* laberinto)
{
    laberinto->actual.x = laberinto->salida.x;
    laberinto->actual.y = laberinto->salida.y-1;
    laberinto->tablero[laberinto->actual.y][laberinto->actual.x] = LUGAR_VACIO;
}

void generarCaminoPrincipalLab(tTablero* laberinto, tpila* historial,tLista* futurosCaminos)
{
    tCoordenadas meta = {laberinto->entrada.x,PRIMER_INTERIOR_FILA};
    int vecinoNro;
    while(laberinto->tablero[meta.y][meta.x]==CARACTER_PARED){
        calcularVecinosDisponiblesPrincipalLab(laberinto);
        if(laberinto->vecinos.cantidad > 0)
        {
            for(vecinoNro=0;vecinoNro<laberinto->vecinos.cantidad;vecinoNro++){
                insertarOrdenadoLista(futurosCaminos,&laberinto->vecinos.vecino[vecinoNro],sizeof(tCoordenadas),cmpVecino,SIN_DUPLICADO,NULL);
            }
            apilarPila(historial, &laberinto->actual, sizeof(tCoordenadas));
            trazarCaminoHaciaVecinoPrincipalLab(laberinto);
            sacarPorClaveOrdenadoLista(futurosCaminos,&laberinto->actual,sizeof(tCoordenadas),cmpVecino);
        }
        else
        {
            desapilarPila(historial, &laberinto->actual, sizeof(tCoordenadas));
        }
    }
}

void trazarCaminoHaciaVecinoPrincipalLab(tTablero* laberinto){
    tCoordenadas intermedio;
    tCoordenadas anterior = laberinto->actual;
    int eleccion = obtenerNumeroAleatorio(0, laberinto->vecinos.cantidad - 1);
    laberinto->actual = laberinto->vecinos.vecino[eleccion];
    intermedio = calcularCeldaIntermediaLab(&anterior,&laberinto->actual);
    laberinto->tablero[intermedio.y][intermedio.x] = LUGAR_VACIO;
    if(laberinto->actual.y != BORDE_SUPERIOR && laberinto->actual.x != BORDE_IZQUIERDO && laberinto->actual.x != BORDE_DERECHO(laberinto->limite.x)){
        laberinto->tablero[laberinto->actual.y][laberinto->actual.x] = LUGAR_VACIO;
    }else{
        laberinto->actual = intermedio;
    }
}

tCoordenadas calcularCeldaIntermediaLab(const tCoordenadas* origen, const tCoordenadas* destino)
{
    tCoordenadas intermedia;
    intermedia.x = (origen->x + destino->x) / 2;
    intermedia.y = (origen->y + destino->y) / 2;
    return intermedia;
}

void calcularVecinosDisponiblesPrincipalLab(tTablero* laberinto)
{
    int desplazamientoX[MAX_DESPLAZAMIENTOS]={-SALTO_CELDA,SALTO_CELDA,0,0};
    int desplazamientoY[MAX_DESPLAZAMIENTOS]={0,0,-SALTO_CELDA,SALTO_CELDA};
    int filaVecina, columnaVecina;
    int cantidadVecinos = 0;
    for(int despla=0;despla< MAX_DESPLAZAMIENTOS;despla++)
    {
        columnaVecina = laberinto->actual.x + desplazamientoX[despla];
        filaVecina = laberinto->actual.y + desplazamientoY[despla];
        if (esVecinoValidoPrincipalLab(laberinto, filaVecina, columnaVecina))
        {
            laberinto->vecinos.vecino[cantidadVecinos].x = columnaVecina;
            laberinto->vecinos.vecino[cantidadVecinos].y = filaVecina;
            cantidadVecinos++;
        }
    }
    laberinto->vecinos.cantidad = cantidadVecinos;
}

int esVecinoValidoPrincipalLab(const tTablero* laberinto, int fila, int columna){
    if(fila < BORDE_SUPERIOR || fila >= BORDE_INFERIOR(laberinto->limite.y)){
        return NO_VALIDO;
    }
    if(fila > PRIMER_INTERIOR_FILA){
        if(columna <= BORDE_IZQUIERDO || columna >= BORDE_DERECHO(laberinto->limite.x)){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila][columna] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila+1][columna] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila-1][columna] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila][columna-1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila][columna+1] != CARACTER_PARED){
            return NO_VALIDO;
        }
    }else{
        if(columna < BORDE_IZQUIERDO || columna > BORDE_DERECHO(laberinto->limite.x)){
            return NO_VALIDO;
        }
        if(columna == BORDE_IZQUIERDO && laberinto->tablero[fila][columna+1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(columna == BORDE_DERECHO(laberinto->limite.x) && laberinto->tablero[fila][columna-1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila][columna] != CARACTER_PARED && (columna-1)==BORDE_IZQUIERDO && laberinto->tablero[fila][columna+1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila][columna] != CARACTER_PARED && (columna+1)==BORDE_DERECHO(laberinto->limite.x)
                && laberinto->tablero[fila][columna-1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(columna>BORDE_IZQUIERDO && laberinto->tablero[fila][columna] != CARACTER_PARED && laberinto->tablero[fila][columna-1] != CARACTER_PARED && laberinto->tablero[fila][columna+1] != CARACTER_PARED){
            return NO_VALIDO;
        }
        if(fila>BORDE_SUPERIOR && columna>BORDE_IZQUIERDO && laberinto->tablero[fila][columna] != CARACTER_PARED && laberinto->tablero[fila-1][columna-1] != CARACTER_ENTRADA && laberinto->tablero[fila-1][columna+1] != CARACTER_ENTRADA){
            return NO_VALIDO;
        }
    }
    return SI_VALIDO;
}



void generarCaminosExtrasLab(tTablero* laberinto,tLista* futurosCaminos){
    tCoordenadas camino;
    while(!listaVacia(futurosCaminos)){
        sacarUltimoLista(futurosCaminos,&camino,sizeof(tCoordenadas));
        trazarCaminoHastaDondeLlegueExtraLab(laberinto,camino);
    }
}


void trazarCaminoHastaDondeLlegueExtraLab(tTablero* laberinto,tCoordenadas camino){
    if(!esExtraValidoExtraLab(laberinto,camino.y,camino.x)){
        return;
    }
    laberinto->actual = camino;
    conectarConCaminoPrincipalExtra(laberinto);
    do{
    calcularExtrasDisponiblesExtraLab(laberinto,SALTO_CELDA,esExtraValidoExtraLab);
        if(laberinto->vecinos.cantidad > 0){
            trazarCaminosExtrasLab(laberinto);
        }
    }while(laberinto->vecinos.cantidad>0);
}

void trazarCaminosExtrasLab(tTablero* laberinto){
    int indiceAleatorio = rand() % laberinto->vecinos.cantidad;
    tCoordenadas origen = laberinto->actual;
    tCoordenadas intermedio;
    int vecinoNro;
    for(vecinoNro=0;vecinoNro<laberinto->vecinos.cantidad;vecinoNro++){
        laberinto->actual = laberinto->vecinos.vecino[vecinoNro];
        intermedio = calcularCeldaIntermediaLab(&origen,&laberinto->actual);
        laberinto->tablero[intermedio.y][intermedio.x] = LUGAR_VACIO;
        if(laberinto->actual.y != BORDE_SUPERIOR && laberinto->actual.x != BORDE_IZQUIERDO && laberinto->actual.x != BORDE_DERECHO(laberinto->limite.x)){
            laberinto->tablero[laberinto->actual.y][laberinto->actual.x] = LUGAR_VACIO;
        }
    }
    laberinto->actual = laberinto->vecinos.vecino[indiceAleatorio];
}


void conectarConCaminoPrincipalExtra(tTablero* laberinto){
    tCoordenadas coneccion;
    tCoordenadas destino;
    int fila,columna;
    int desplazamientoX[MAX_DESPLAZAMIENTOS]={-SALTO_CELDA,SALTO_CELDA,0,0};
    int desplazamientoY[MAX_DESPLAZAMIENTOS]={0,0,-SALTO_CELDA,SALTO_CELDA};
    int despla=0;
    while(laberinto->tablero[laberinto->actual.y][laberinto->actual.x]!=LUGAR_VACIO && despla<MAX_DESPLAZAMIENTOS){
        columna = laberinto->actual.x + desplazamientoX[despla];
        fila = laberinto->actual.y + desplazamientoY[despla];
        if(laberinto->tablero[fila][columna]==LUGAR_VACIO)
        {
            destino.x=columna;
            destino.y=fila;
            coneccion = calcularCeldaIntermediaLab(&laberinto->actual,&destino);
            laberinto->tablero[coneccion.y][coneccion.x]=LUGAR_VACIO;
            laberinto->tablero[laberinto->actual.y][laberinto->actual.x] = LUGAR_VACIO;
        }
        despla++;
    }
}

int esExtraValidoExtraLab(tTablero* laberinto,int fila,int columna){
    if(fila <= BORDE_SUPERIOR || fila >= BORDE_INFERIOR(laberinto->limite.y)){
        return NO_VALIDO;
    }
    if(columna <= BORDE_IZQUIERDO || columna >= BORDE_DERECHO(laberinto->limite.x)){
        return NO_VALIDO;
    }
    if(laberinto->tablero[fila][columna] != CARACTER_PARED){
        return NO_VALIDO;
    }
    if(laberinto->tablero[fila-1][columna] != CARACTER_PARED || laberinto->tablero[fila+1][columna] != CARACTER_PARED || laberinto->tablero[fila][columna+1] != CARACTER_PARED || laberinto->tablero[fila][columna-1] != CARACTER_PARED){
        return NO_VALIDO;
    }
    return SI_VALIDO;
}

void calcularExtrasDisponiblesExtraLab(tTablero* laberinto,int salto,Validacion valido){
    int desplazamientoX[MAX_DESPLAZAMIENTOS]={-salto,salto,0,0};
    int desplazamientoY[MAX_DESPLAZAMIENTOS]={0,0,-salto,salto};
    int filaVecina, columnaVecina;
    int cantidadVecinos = 0;
    for(int despla=0;despla< MAX_DESPLAZAMIENTOS;despla++)
    {
        columnaVecina = laberinto->actual.x + desplazamientoX[despla];
        filaVecina = laberinto->actual.y + desplazamientoY[despla];
        if (valido(laberinto, filaVecina, columnaVecina))
        {
            laberinto->vecinos.vecino[cantidadVecinos].x = columnaVecina;
            laberinto->vecinos.vecino[cantidadVecinos].y = filaVecina;
            cantidadVecinos++;
        }
    }
    laberinto->vecinos.cantidad = cantidadVecinos;
}

void generarAberturasDeCaminosLab(tTablero* laberinto) {
    int filasInternas = laberinto->limite.y - 2;
    int columnasInternas = laberinto->limite.x - 2;
    int celdasInternas = filasInternas * columnasInternas;
    int paredesARomper = (int)(celdasInternas * DENSIDAD);
    int aberturas = 0;

    int maxFilasElegidas = filasInternas / 2;
    if (maxFilasElegidas < 2)
        maxFilasElegidas = filasInternas;

    int filasElegidas[filasInternas];
    for (int i = 0; i < filasInternas; i++)
        filasElegidas[i] = i + 1;

    // Mezclar filas aleatoriamente (Fisher-Yates)
    for (int i = filasInternas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = filasElegidas[i];
        filasElegidas[i] = filasElegidas[j];
        filasElegidas[j] = temp;
    }

    // 🔓 Fila de entrada completamente libre
    for (int j = 1; j < laberinto->limite.x - 1; j++) {
        if (laberinto->tablero[PRIMER_INTERIOR_FILA][j] != 'E') {
            laberinto->tablero[PRIMER_INTERIOR_FILA][j] = LUGAR_VACIO;
        }
    }

    // 🔓 Fila de salida completamente libre
    int filaSalida = ULTIMO_INTERIOR_FILA(laberinto->limite.y);
    for (int j = 1; j < laberinto->limite.x - 1; j++) {
        if (laberinto->tablero[filaSalida][j] != 'S') {
            laberinto->tablero[filaSalida][j] = LUGAR_VACIO;
        }
    }

    // 🌀 ABERTURAS ALEATORIAS GENERALES
    int filasUsadas = (paredesARomper / 2 < maxFilasElegidas) ? (paredesARomper / 2) : maxFilasElegidas;

    for (int i = 0; i < filasUsadas && aberturas < paredesARomper; i++) {
        int fila = filasElegidas[i];
        // Evitamos modificar filas de entrada y salida
        if (fila == PRIMER_INTERIOR_FILA || fila == filaSalida)
            continue;

        int columnasElegidas[columnasInternas];
        for (int j = 0; j < columnasInternas; j++)
            columnasElegidas[j] = j + 1;

        // Mezclar columnas
        for (int j = columnasInternas - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = columnasElegidas[j];
            columnasElegidas[j] = columnasElegidas[k];
            columnasElegidas[k] = temp;
        }

        int maxAberturasFila = 1 + rand() % 3;
        int aberturasPorFila = 0;

        for (int j = 0; j < columnasInternas && aberturasPorFila < maxAberturasFila && aberturas < paredesARomper; j++) {
            int columna = columnasElegidas[j];
            if (esAberturaValidaLab(laberinto, fila, columna)) {
                laberinto->tablero[fila][columna] = LUGAR_VACIO;
                aberturas++;
                aberturasPorFila++;
            }
        }
    }

//    printf("Aberturas creadas: %d de %d\n", aberturas, paredesARomper);
}

int esAberturaValidaLab(const tTablero* laberinto,int fila,int columna){
    int paredesVecinas=0;
    tCoordenadas actual={columna,fila};
    if(laberinto->tablero[fila][columna]==LUGAR_VACIO){
        return NO_VALIDO;
    }
    contarParedesVecinas(laberinto,actual,&paredesVecinas);
    if(paredesVecinas!=2){
        return NO_VALIDO;
    }
    if(fila!=PRIMER_INTERIOR_FILA && fila!=ULTIMO_INTERIOR_FILA(laberinto->limite.y) && columna!=ULTIMO_INTERIOR_COL(laberinto->limite.x) && columna!=PRIMER_INTERIOR_COL){
        if(laberinto->tablero[fila-1][columna]==CARACTER_PARED && (laberinto->tablero[fila][columna-1]==CARACTER_PARED || laberinto->tablero[fila][columna+1]==CARACTER_PARED)){
            return NO_VALIDO;
        }
        if(laberinto->tablero[fila+1][columna]==CARACTER_PARED && (laberinto->tablero[fila][columna-1]==CARACTER_PARED || laberinto->tablero[fila][columna+1]==CARACTER_PARED)){
            return NO_VALIDO;
        }
    }
    if(columna==PRIMER_INTERIOR_COL && fila==PRIMER_INTERIOR_FILA){
        return NO_VALIDO;
    }
    return SI_VALIDO;
}

void contarParedesVecinas(const tTablero* laberinto,tCoordenadas actual,int* paredesVecinas){
    int contador=0;
    if(actual.y!=PRIMER_INTERIOR_FILA && laberinto->tablero[actual.y-1][actual.x]==CARACTER_PARED){
        contador++;
    }
    if(actual.y!=ULTIMO_INTERIOR_FILA(laberinto->limite.y) && laberinto->tablero[actual.y+1][actual.x]==CARACTER_PARED){
        contador++;
    }
    if(actual.x!=PRIMER_INTERIOR_COL && laberinto->tablero[actual.y][actual.x-1]==CARACTER_PARED){
        contador++;
    }
    if(actual.x!=ULTIMO_INTERIOR_COL(laberinto->limite.x) && laberinto->tablero[actual.y][actual.x+1]==CARACTER_PARED){
        contador++;
    }
    *paredesVecinas=contador;
}

int cmpVecino(const void* a, const void* b) {
    tCoordenadas* primero = (tCoordenadas*)a;
    tCoordenadas* segundo = (tCoordenadas*)b;
    if (primero->y != segundo->y)
        return primero->y - segundo->y;
    return primero->x - segundo->x;
}



