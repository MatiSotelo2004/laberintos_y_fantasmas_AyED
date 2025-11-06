#include "tda_cola_dinamica.h"

void crearCola(tCola* cola){
    cola->pri = cola->ult = NULL;
}
int ponerCola(tCola* cola,const void* dato,unsigned tam){
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));
    void* info=malloc(tam);
    if(!nue || !info){
        free(info);
        free(nue);
        return SIN_MEMORIA;
    }
    nue->dato=info;
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=NULL;
    if(!cola->pri){
        cola->pri=nue;
    }else{
        cola->ult->sig=nue;
    }
    cola->ult=nue;
    return TODO_OK;
}
int sacarCola(tCola* cola,void* dato,unsigned tam){
    tNodo* elim = cola->pri;
    if(!cola->pri)
        return COLA_VACIA;
    memcpy(dato,elim->dato,MIN(elim->tam,tam));
    cola->pri=elim->sig;
    free(elim->dato);
    free(elim);
    if(!cola->pri)
        cola->ult = NULL;
    return TODO_OK;
}
void vaciarCola(tCola* cola){
    tNodo* elim = cola->pri;
    while(cola->pri){
        cola->pri=elim->sig;
        free(elim->dato);
        free(elim);
        elim=cola->pri;
    }
    cola->ult=cola->pri;
}
int verPrimero(const tCola* cola,void* dato,unsigned tam){
    if(!cola->pri)
        return COLA_VACIA;
    memcpy(dato,cola->pri->dato,MIN(cola->pri->tam,tam));
    return TODO_OK;
}
int colaLlena(const tCola* cola,unsigned tam){
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);
    free(nue);
    free(info);
    return !nue || !info;
}
int colaVacia(const tCola* cola){
    return cola->pri == NULL;
}
