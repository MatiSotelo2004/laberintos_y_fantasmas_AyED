#include "juego.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

int jugarPartida(FILE* partida,tCola* registroJugador,tConfiguracion *configuracion, tJugador *jugador,const char *nomJugador)
{
    srand(time(NULL));
    tMovimiento movimientosJugador;
    tCola colaMovimientos;
    tTablero tablero;
    tPortal portal;
    tFantasmas fantasmas;
    tCoordenadas posicionJugador;
    tCoordenadas posicionFantasma;
    tCoordenadas coordenadaEntrada;
    tCoordenadas coordenadaSalida;
    char objeto;
    char movimiento;
    tCoordenadas limiteTablero = obtenerTamTablero(configuracion);
    int cantPremios = obtenerCantPremos(configuracion);
    int cantVidasInicial = obtenerCantVidasInicial(configuracion);
    int cantVidasExtra = obtenerCantVidasExtra(configuracion);
    int cantFantasmas = obtenerCantFantasmas(configuracion);

    crearCola(&colaMovimientos);

    crearTablero(&tablero,limiteTablero);
    tableroInicializar(&tablero, CARACTER_PARED); /// se pueden modularizar
    tableroDibujarParedes(&tablero); /// se pueden modularizar
    generarLaberinto(&tablero);

    coordenadaEntrada=obtenerEntradaTablero(&tablero);
    coordenadaSalida=obtenerSalidaTablero(&tablero);

    crearFantasmas(&fantasmas,cantFantasmas);
    tableroColocarObjetosAleatorio(&tablero, cantPremios, CARACTER_PREMIO);
    tableroColocarObjetosAleatorio(&tablero, cantVidasExtra, CARACTER_VIDA);
    tableroColocarFantasmasAleatorio(&tablero,obtenerPunteroFantasmas(&fantasmas), cantFantasmas, CARACTER_FANTASMA);
    if(crearPortalEnTablero(&portal,&tablero) != PORTAL_CREADO_EXITOSO)
        puts("AVISO: NO SE PUDO INICALIZAR PORTAL!");

    inicializarJugador(jugador,&coordenadaEntrada,cantVidasInicial,nomJugador);

    system("cls");
    imprimirJugador(jugador);
    imprimirTablero(&tablero,partida);
    imprimirTablero(&tablero,stdout);

    while(!coordenadasSonIguales(&coordenadaSalida,obtenerPunteroJugador(jugador)) && obtenerVidasJugador(jugador) > 0)
    {
        do{
            posicionJugador = obtenerCoordenadasJugador(jugador);
            solicitarMovimiento(&movimiento);
            coordenadaEjecutarMovimiento(&posicionJugador,movimiento);
            obtenerObjetoPosicionTablero(&tablero,&posicionJugador,&objeto);
        }while(objeto == CARACTER_INVALIDO || objeto==CARACTER_PARED);

        cargarMovimiento(&movimientosJugador,obtenerPunteroJugador(jugador),objeto);

        ponerCola(registroJugador,&movimientosJugador,sizeof(tMovimiento));
        ponerCola(&colaMovimientos,&posicionJugador,sizeof(tCoordenadas));

        for(int nroFantasma = 0; nroFantasma < cantFantasmas;nroFantasma++)
        {
            posicionFantasma = obtenerCoordenadasFantasmas(&fantasmas,nroFantasma);
            posicionFantasma = fantasmaObtenerSiguienteMovimiento(&tablero,&posicionFantasma,&posicionJugador);
            ponerCola(&colaMovimientos,&posicionFantasma,sizeof(tCoordenadas));
        }

        ejecutarMovimientosTablero(&colaMovimientos,&tablero, jugador,&fantasmas,&cantFantasmas,&portal);
        system("cls");
        imprimirJugador(jugador);
        imprimirTablero(&tablero,stdout);
    }


    if(coordenadasSonIguales(&coordenadaSalida,obtenerPunteroJugador(jugador))){
        sumarPuntajeJugador(jugador, CANT_PUNTAJE_POR_GANAR);
        puts(MENSAJE_VICTORIA);
        printf("Tu puntaje en esta partida ha sido: %d\n",obtenerPuntajeJugador(jugador));
        puts(MENSAJE_AGRADECIMIENTO);
        mostrarRegistroJugador(registroJugador,partida);
    }
    if(obtenerVidasJugador(jugador)==0){
        puts(MENSAJE_DERROTA);
        puts(MENSAJE_MOTIVACION);
        mostrarRegistroJugador(registroJugador,partida);
    }
    vaciarCola(&colaMovimientos);
    destruirFantasmas(&fantasmas);
    destruirTablero(&tablero);
    system("pause");
    return 0;
}

tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posFantasma, const tCoordenadas *posJugador)
{
    int nroMovimiento;
    tCoordenadas siguienteMovimiento = *posFantasma;
    tCoordenadas *movimientos = obtenerMovimientosTablero(tablero, posFantasma);
    tCoordenadas *movimientoAtual;
    if (movimientos == MOVIMIENTOS_SIN_MEMORIA)
        return *posFantasma;
    double distanciaActual = obtenerDistancia(posJugador, posFantasma);
    double mejorDistancia = distanciaActual;
    int cantMovimientosFantasma = (distanciaActual < 4.0) ? 4 : 8;

    for (nroMovimiento = 0; nroMovimiento < cantMovimientosFantasma; nroMovimiento++)
    {
        movimientoAtual = movimientos + nroMovimiento;

        if (movimientoAtual->x != POSICION_NO_DISPONIBLE && movimientoAtual->y != POSICION_NO_DISPONIBLE)
        {
            distanciaActual = obtenerDistancia(movimientoAtual, posJugador);

            if (distanciaActual < mejorDistancia)
            {
                mejorDistancia = distanciaActual;
                coordenadasCopiar(movimientoAtual, &siguienteMovimiento);
            }
        }
    }
    free(movimientos);
    return siguienteMovimiento;
}


void ejecutarMovimientosTablero(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tFantasmas *fantasmas,int* cantFantasmas, const tPortal *portal)
{
    int nroFantasma = 0;
    char objeto;
    tCoordenadas posicionJugador;
    tCoordenadas posicionFantasma;
    tCoordenadas* posicionActualFantasma;
    tCoordenadas entradaTablero = obtenerEntradaTablero(tablero);
    tCoordenadas* posicionActualJugador = obtenerPunteroJugador(jugador);

    sacarCola(colaMovimientos,&posicionJugador,sizeof(tCoordenadas));

    while(!colaVacia(colaMovimientos))
    {
        sacarCola(colaMovimientos,&posicionFantasma,sizeof(tCoordenadas));
        obtenerObjetoPosicionTablero(tablero,&posicionFantasma,&objeto);

        if(objeto != CARACTER_PARED
        && objeto != CARACTER_PREMIO
        && objeto != CARACTER_VIDA
        && objeto != CARACTER_FANTASMA
        && objeto != CARACTER_PORTAL)
        {
            posicionActualFantasma=obtenerPunteroNroFantasmas(fantasmas,nroFantasma);
            colocarObjetoPosicionTablero(tablero,&posicionFantasma,CARACTER_FANTASMA);
            colocarObjetoPosicionTablero(tablero,posicionActualFantasma,LUGAR_VACIO);
            coordenadasCopiar(&posicionFantasma,posicionActualFantasma);
        }

        nroFantasma++;
    }


    obtenerObjetoPosicionTablero(tablero,&posicionJugador,&objeto);

    switch(objeto){
        case CARACTER_PREMIO:
        sumarPuntajeJugador(jugador,CANT_PUNTAJE_POR_PREMIO_TABLERO);
        break;
        case CARACTER_VIDA:
        sumarVidaJugador(jugador);
        break;
        case CARACTER_FANTASMA:
        restarVidaJugador(jugador);
        coordenadasCopiar(&entradaTablero,&posicionJugador);
        eliminarFantasmaTablero(tablero,fantasmas,cantFantasmas);
        tableroColocarFantasmasAleatorio(tablero,obtenerPunteroFantasmas(fantasmas),*cantFantasmas, CARACTER_FANTASMA);
        break;
        case CARACTER_PORTAL:
        portalTeletransportar(portal,&posicionJugador);
        break;
    }

    if(coordenadasSonIguales(posicionActualJugador,&entradaTablero)){
        colocarObjetoPosicionTablero(tablero,posicionActualJugador,CARACTER_ENTRADA);
    }else{
        colocarObjetoPosicionTablero(tablero,posicionActualJugador,LUGAR_VACIO);
    }

    colocarObjetoPosicionTablero(tablero,&posicionJugador,CARACTER_JUGADOR);
    moverJugador(jugador,&posicionJugador);
    sumarCantMovimientosJugador(jugador);
}

void eliminarFantasmaTablero(tTablero* tablero,tFantasmas* fantasma,int* cantFantasmas){
    int nroFantasma;
    tCoordenadas fantasmaActual;
    for(nroFantasma=0;nroFantasma<(*cantFantasmas);nroFantasma++){
        fantasmaActual = obtenerCoordenadasFantasmas(fantasma,nroFantasma);
        tablero->tablero[fantasmaActual.y][fantasmaActual.x]=LUGAR_VACIO;
    }
    (*cantFantasmas)--;
}

int crearPortalEnTablero(tPortal *portal, tTablero *tablero)
{
    char objetoEnEntradaDePortal;
    char objetoEnSalidaPortal;
    tCoordenadas entradaPortal;
    tCoordenadas salidaPortal;

    tCoordenadas limiteTablero = obtenerLimiteTablero(tablero);
    unsigned cantIntentos = limiteTablero.y;

    entradaPortal.x = 1;//en realidad va a estar en la columna cero la entrada,
    //pero la inicializo en 1 para ver que objeto hay al lado del portal

    OBTENER_NUM_ALEATORIO(1,limiteTablero.y,entradaPortal.y);
    //limite inferior, limite superior, destino donde voy a poner el numero aleatorio

    obtenerObjetoPosicionTablero(tablero,&entradaPortal,&objetoEnEntradaDePortal);

    while(cantIntentos && (objetoEnEntradaDePortal == CARACTER_PARED || objetoEnEntradaDePortal == CARACTER_FANTASMA))
    {
        OBTENER_NUM_ALEATORIO(1,limiteTablero.y,entradaPortal.y);
        obtenerObjetoPosicionTablero(tablero,&entradaPortal,&objetoEnEntradaDePortal);
        cantIntentos--;
    }

    if(cantIntentos == 0)
        return !PORTAL_CREADO_EXITOSO;

    cantIntentos = limiteTablero.y;
    salidaPortal.x = limiteTablero.x-2;

    OBTENER_NUM_ALEATORIO(1,limiteTablero.y,salidaPortal.y);
    obtenerObjetoPosicionTablero(tablero,&salidaPortal,&objetoEnSalidaPortal);

    while(cantIntentos && (objetoEnSalidaPortal == CARACTER_PARED || objetoEnSalidaPortal == CARACTER_FANTASMA))
    {
        OBTENER_NUM_ALEATORIO(1,limiteTablero.y,salidaPortal.y);
        obtenerObjetoPosicionTablero(tablero,&salidaPortal,&objetoEnSalidaPortal);
        cantIntentos--;
    }

    if(cantIntentos == 0)
        return !PORTAL_CREADO_EXITOSO;

    entradaPortal.x = 0;//lo dejo como deberia estar
    salidaPortal.x = limiteTablero.x-1;
    portalInicializar(portal,&entradaPortal,&salidaPortal);
    tablero->tablero[entradaPortal.y][entradaPortal.x] = portal->simbolo;
    tablero->tablero[salidaPortal.y][salidaPortal.x] = portal->simbolo;
    return PORTAL_CREADO_EXITOSO;
}

void solicitarMovimiento(char *movimiento)
{
    char ingreso = _getch();
    if(ingreso != MOVIMIENTO_ABAJO && ingreso != MOVIMIENTO_ARRIBA
            && ingreso != MOVIMIENTO_IZQUIERDA && ingreso != MOVIMIENTO_DERECHA)
    {
        puts(MENSAJE_RECORDATORIO);
        do{
            ingreso = _getch();
        }while(ingreso != MOVIMIENTO_ABAJO && ingreso != MOVIMIENTO_ARRIBA
                && ingreso != MOVIMIENTO_IZQUIERDA && ingreso != MOVIMIENTO_DERECHA);
    }
    *movimiento = ingreso;
}


void mostrarRegistroJugador(tCola* registroJugador,FILE* partida){
    tMovimiento movimiento;
    int nroMovimiento=1;
        puts(INFORME_JUGADOR);
        fprintf(partida,"\n%s\n",INFORME_JUGADOR);
        while(!colaVacia(registroJugador)){
            sacarCola(registroJugador,&movimiento,sizeof(movimiento));
            printf("Movimiento %2d: y=%2d|x=%2d",nroMovimiento,movimiento.movimiento.y,movimiento.movimiento.x);
            fprintf(partida,"Movimiento %2d: y=%2d|x=%2d",nroMovimiento,movimiento.movimiento.y,movimiento.movimiento.x);
            switch(movimiento.objeto){
                case CARACTER_FANTASMA:
                    puts(INFORME_FANTASMA);
                    fprintf(partida,"%s\n",INFORME_FANTASMA);
                break;
                case CARACTER_PREMIO:
                    puts(INFORME_PREMIO);
                    fprintf(partida,"%s\n",INFORME_PREMIO);
                break;
                case CARACTER_VIDA:
                    puts(INFORME_VIDA);
                    fprintf(partida,"%s\n",INFORME_VIDA);
                break;
                case CARACTER_PORTAL:
                    puts(INFORME_PORTAL);
                    fprintf(partida,"%s\n",INFORME_PORTAL);
                break;
                case CARACTER_SALIDA:
                    puts(INFORME_SALIDA);
                    fprintf(partida,"%s\n",INFORME_SALIDA);
                break;
                default:
                    puts("");
                    fprintf(partida,"\n");
                break;
            }
            nroMovimiento++;
        }

}
