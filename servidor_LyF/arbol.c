#include "arbol.h"

void crearArbol(tArbol *p)
{
    *p = NULL;
}
void destruirArbol(tArbol *p)
{
    if (!*p)
        return;

    destruirArbol(&(*p)->der);
    destruirArbol(&(*p)->izq);
    free((*p)->dato);
    free(*p);
}

int insertarArbolBin(tArbol *p, const void *dato, unsigned tamDato, int (*cmp)(const void *, const void *))
{
    tNodoArbol *nue;

    while (*p)
    {
        if (cmp(dato, (*p)->dato) > 1)
            p = (&(*p)->der);
        else
            p = (&(*p)->izq);
    }
    nue = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if (!nue)
        return SIN_MEM;

    nue->dato = malloc(tamDato);

    if (!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato, dato, tamDato);
    nue->der = NULL;
    nue->izq = NULL;

    *p = nue;

    return TODO_OK;
}

int compararInt(const void *x, const void *y)
{
    int *num1 = (int *)x;
    int *num2 = (int *)y;
    return (*num1) - (*num2);
}

void mapArbol(tArbol *p, void (*accion)(void *))
{
    if (!*p)
        return;

    mapArbol(&(*p)->izq, accion);
    accion((*p)->dato);
    mapArbol(&(*p)->der, accion);
}
void printInt(void *x)
{
    int *num = (int *)x;
    printf("%d ", *num);
}
void postOrden(tArbol *p, void (*accion)(void *))
{
    if (!*p)
        return;

    mapArbol(&(*p)->izq, accion);
    mapArbol(&(*p)->der, accion);
    accion((*p)->dato);
}
void preOrden(tArbol *p, void (*accion)(void *))
{
    if (!*p)
        return;

    accion((*p)->dato);
    mapArbol(&(*p)->izq, accion);
    mapArbol(&(*p)->der, accion);
}
void inOrder(tArbol *p, void (*accion)(void *))
{
    if (!*p)
        return;

    mapArbol(&(*p)->izq, accion);
    accion((*p)->dato);
    mapArbol(&(*p)->der, accion);
}
