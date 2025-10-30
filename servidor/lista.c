#include "lista.h"

void crearLista(tLista *lista)
{
    *lista = NULL;
}

int listaVacia(tLista *lista)
{
    return (*lista) ? LISTA_NO_VACIA : LISTA_VACIA;
}

int listaInsertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, int (*comparar)(const void *, const void *))
{
    tNodoLista *act, *auxSig, *auxAnt, *nue;
    act = *lista;

    if (!act)
    {
        auxAnt = NULL;
        auxSig = NULL;
    }
    else
    {
        while (act->ant && comparar(act->dato, dato) > 0)
        {
            act = act->ant;
        }
        while (act->sig && comparar(dato, act->dato) > 0)
        {
            act = act->sig;
        }

        if (comparar(dato, act->dato) > 0)
        {
            auxAnt = act;
            auxSig = act->sig;
        }
        else
        {
            auxAnt = act->ant;
            auxSig = act;
        }
    }

    nue = (tNodoLista *)malloc(sizeof(tNodoLista));
    if (!nue)
        return SIN_MEM;
    nue->dato = malloc(tamDato);
    if (!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->ant = auxAnt;
    nue->sig = auxSig;

    if (auxAnt)
        auxAnt->sig = nue;
    if (auxSig)
        auxSig->ant = nue;

    *lista = nue;

    return TODO_OK;
}

int listaSacarPrimero(tLista *lista, void *dato, unsigned tamDato)
{
    tNodoLista *elim = *lista;

    if (!elim)
        return LISTA_VACIA;

    while (elim->ant)
    {
        elim = elim->ant;
    }

    *lista = elim->sig;
    if (*lista)
        (*lista)->ant = NULL;

    memcpy(dato, elim->dato, MIN(elim->tamDato, tamDato));
    free(elim->dato);
    free(elim);

    return TODO_OK;
}

void destruirLista(tLista *lista)
{
    tNodoLista *aux;

    while ((*lista)->ant)
        lista = &((*lista)->ant);

    while (*lista)
    {
        aux = *lista;
        lista = &((*lista)->sig);
        free(aux->dato);
        free(aux);
    }
}
