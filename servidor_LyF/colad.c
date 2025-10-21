#include "colad.h"

void crearCola(tCola *cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}
int encolarCola(tCola *cola, const void *dato, unsigned tamDato)
{
    tNodo *temp;

    if (!(temp = (tNodo *)malloc(sizeof(tNodo))))
        return ERROR;

    if (!(temp->dato = malloc(tamDato)))
    {
        free(temp);
        return ERROR;
    }

    memcpy(temp->dato, dato, tamDato);
    temp->tamDato = tamDato;
    temp->sig = NULL;

    if (cola->ult)
    {
        cola->ult->sig = temp;
    }
    else
    {
        cola->pri = temp;
    }
    cola->ult = temp;

    return TODO_OK;
}
int descolarCola(tCola *cola, void *dato, unsigned tamDato)
{
    tNodo *temp = cola->pri;
    if (!temp)
        return ERROR;
    memcpy(dato, temp->dato, MIN(tamDato, temp->tamDato));
    cola->pri = temp->sig;
    free(temp->dato);
    free(temp);

    return TODO_OK;
}
int colaLlena(const tCola *cola, unsigned tamDato)
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
int colaVacia(const tCola *cola)
{
    return (cola->pri == NULL);
}
int verPrimero(const tCola *cola, void *dato, unsigned tamDato)
{
    if (!cola->pri)
        return ERROR;
    memcpy(dato, cola->pri->dato, MIN(tamDato, cola->pri->tamDato));
    return TODO_OK;
}
void destruirCola(tCola *cola)
{
    tNodo *temp;

    while (cola->pri)
    {
        temp = cola->pri;
        cola->pri = temp->sig;
        free(temp->dato);
        free(temp);
    }
    return;
}