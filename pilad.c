#include "pilad.h"

void crearPila(tpila *pila)
{
    (*pila) = NULL;
    return;
}

int apilarPila(tpila *pila, const void *dato, unsigned tamDato)
{

    tNodo *datoTemp;

    if (!(datoTemp = (tNodo *)malloc(sizeof(tNodo))))
        return ERROR_PILA;
    if (!(datoTemp->dato = malloc(tamDato)))
    {
        free(datoTemp);
        return ERROR_PILA;
    }

    memcpy(datoTemp->dato, dato, tamDato);
    datoTemp->tam = tamDato;
    datoTemp->sig = *pila;
    *pila = datoTemp;

    return TODO_OK;
}
int desapilarPila(tpila *pila, void *dato, unsigned tamDato)
{
    tNodo *temp;
    if (!*pila)
    {
        return ERROR_PILA;
    }
    memcpy(dato, (*pila)->dato, MIN(tamDato, (*pila)->tam));
    temp = *pila;
    *pila = (*pila)->sig;
    free(temp->dato);
    free(temp);

    return TODO_OK;
}
int pilaVacia(const tpila *pila)
{
    return (*pila == NULL);
}
int pilaLlena(const tpila *pila, unsigned tamDato)
{
    tNodo *temp;

    if (!(temp = (tNodo *)malloc(sizeof(tNodo))))
        return 1;

    if (!(temp->dato = malloc(tamDato)))
    {
        free(temp);
        return 1;
    }

    free(temp->dato);
    free(temp);

    return 0;
}
int verTope(const tpila *pila, void *dato, unsigned tamDato)
{
    if (!*pila)
        return ERROR_PILA;

    memcpy(dato, (*pila)->dato, MIN(tamDato, (*pila)->tam));

    return TODO_OK;
}
void destruirPila(tpila *pila)
{
    tNodo *temp;

    while (*pila)
    {
        temp = *pila;
        *pila = temp->sig;
        free(temp->dato);
        free(temp);
    }
    return;
}
