#include"arbol.h"


void crearArbol(tArbol*p)
{
    *p=NULL;
}
void destruirArbol(tArbol*p)
{
    if(!*p)
        return;

    destruirArbol(&(*p)->der);
    destruirArbol(&(*p)->izq);
    free((*p)->dato);
    free(*p);
}

int insertarArbolBinNoR(tArbol*p, const void*dato, unsigned tamDato, int (*cmp)(const void*, const void*))
{
    tNodoArbol* nue;

    while(*p)
    {
        if(cmp(dato, (*p)->dato)>1)
            p = (&(*p)->der);
        else
            p =(&(*p)->izq);
    }
    nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!nue)
        return SIN_MEM;

    nue->dato=malloc(tamDato);

    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato, dato, tamDato);
    nue->der=NULL;
    nue->izq=NULL;
    nue->tamDato = tamDato;

    *p=nue;

    return TODO_OK;
}

int insertarArbolBinConR(tArbol*p, const void*dato, unsigned tamDato, int (*cmp)(const void*, const void*))
{
    tNodoArbol *nue;
    if(!*p)
    {
        nue=(tNodoArbol*)malloc(sizeof(tNodoArbol));
        if(!nue)
        {
            return SIN_MEM;
        }
        nue->dato=malloc(tamDato);
        if(!nue->dato)
        {
            free(nue);
            return SIN_MEM;
        }
        memcpy(nue->dato, dato, tamDato);
        nue->der=NULL;
        nue->izq=NULL;
        nue->tamDato = tamDato;

        *p=nue;

        return TODO_OK;
    }

    if(cmp(dato, (*p)->dato) > 0)
        return insertarArbolBinConR(&(*p)->der, dato, tamDato, cmp);
    else
        return insertarArbolBinConR(&(*p)->izq, dato, tamDato, cmp);


}

int compararInt(const void*x, const void*y)
{
    int*num1 = (int*)x;
    int*num2 = (int*)y;
    return (*num1) - (*num2);
}

void printInt(void*x)
{
    int* num = (int*)x;
    printf("%d ", *num);
}
void postOrden(tArbol*p, void *extra, Accion accion)
{
    if(!*p)
        return;

    postOrden(&(*p)->izq, extra, accion);
    postOrden(&(*p)->der, extra, accion);
    accion((*p)->dato,extra);
}
void preOrden(tArbol*p, void *extra, Accion accion)
{
    if(!*p)
        return;

    accion((*p)->dato,extra);
    preOrden(&(*p)->izq, extra, accion);
    preOrden(&(*p)->der, extra, accion);
}
void inOrder(tArbol*p, void *extra, Accion accion)
{
    if(!*p)
        return;

    inOrder(&(*p)->izq, extra, accion);
    accion((*p)->dato,extra);
    inOrder(&(*p)->der, extra, accion);
}

int cantHojas(tArbol*p)
{
    int cant=0;
    if(!*p)
    {
        return 0;
    }
    if(!(*p)->izq && !(*p)->der)
        return 1;
    cant +=cantHojas(&((*p)->izq));
    cant +=cantHojas(&((*p)->der));
    return cant;
}
int cantNoHojas(tArbol*p)
{
    int cant=0;
    if(!*p)
    {
        return 0;
    }
    cant +=cantNoHojas(&((*p)->izq));
    cant +=cantNoHojas(&((*p)->der));
    if((*p)->izq || (*p)->der)
        return cant+1;
    else
        return 0;

}

int arbolAltura(const tArbol *ar)
{
    int hi,hd;
    if(!*ar)
        return 0;


    hi = arbolAltura(&((*ar)->izq));
    hd = arbolAltura(&((*ar)->der));
    return (hi > hd ? hi+1 : hd+1);
}

int arbolNivel(const tArbol *ar)
{
    int hi,hd;
    if(!*ar)
        return -1;


    hi = arbolNivel(&((*ar)->izq));
    hd = arbolNivel(&((*ar)->der));
    return (hi > hd ? hi+1 : hd+1);
}

void arbolAccionHastaNivel(const tArbol *ar, int nivel, void *extra, int incluyeNivel, Accion accion)
{
    if(!*ar || nivel - (-incluyeNivel) == 0)
        return;

    accion((*ar)->dato,extra);
    arbolAccionHastaNivel((&((*ar)->izq)),nivel-1,extra,incluyeNivel,accion);
    arbolAccionHastaNivel((&((*ar)->der)),nivel-1,extra,incluyeNivel,accion);
}

void arbolAccionEnNivel(const tArbol *ar, int nivel, void *extra,Accion accion)
{
    if(!*ar)
        return;

    if(!nivel)
    {
        accion((*ar)->dato,extra);
        return;
    }

    arbolAccionEnNivel((&((*ar)->izq)),nivel-1,extra,accion);
    arbolAccionEnNivel((&((*ar)->der)),nivel-1,extra,accion);

}

void arbolAccionDespuesNivel(const tArbol *ar, int nivel, void *extra, int incluyeNivel, Accion accion)
{
    if(!*ar)
        return;

    if(nivel-incluyeNivel < 0)
        accion((*ar)->dato,extra);

    arbolAccionDespuesNivel((&((*ar)->izq)),nivel-1,extra,incluyeNivel,accion);
    arbolAccionDespuesNivel((&((*ar)->der)),nivel-1,extra,incluyeNivel,accion);

}

void arbolDestruirAPartirDeNivel(tArbol *ar, int nivel)
{
    if(!*ar)
        return;

    arbolDestruirAPartirDeNivel((&((*ar)->izq)),nivel-1);
    arbolDestruirAPartirDeNivel((&((*ar)->der)),nivel-1);

    if(nivel < 0)
    {
        free((*ar)->dato);
        free(*ar);
        *ar = NULL;
    }

}

tArbol *arbolBuscar(tArbol *ar, const void *key, Cmp cmp)
{
    if(!*ar)
        return NULL;

    if(cmp(key, (*ar)->dato) > 0)
        return arbolBuscar(&(*ar)->der,key,cmp);

    if(cmp(key,(*ar)->dato) < 0)
        return arbolBuscar(&(*ar)->izq,key,cmp);

    return ar;

}

tArbol *arbolBuscarMayor(tArbol *ar)
{
    if(!(*ar)->der)
        return ar;

    return arbolBuscarMayor(&(*ar)->der);
}

tArbol *arbolBuscarMenor(tArbol *ar)
{
    if(!(*ar)->izq)
        return ar;

    return arbolBuscarMayor(&(*ar)->izq);
}

int arbolEliminarNodo(tArbol *ar, const void *key, Cmp cmp)
{
    tArbol *elim = arbolBuscar(ar,key,cmp);
    if(!*elim)
        return 0;

    free((*elim)->dato);
    if(!(*elim)->izq && !(*elim)->der)
    {
        free(*elim);
        *elim = NULL;
        return 1;
    }

    arbolEliminarRaiz(elim);
    return 1;

}

void arbolEliminarRaiz(tArbol *ar)
{
    tArbol *elim;
    int hi = arbolAltura(&(*ar)->izq);
    int hd = arbolAltura(&(*ar)->der);
    if(hi > hd)
        elim = arbolBuscarMayor(&(*ar)->izq);
    else
        elim = arbolBuscarMenor(&(*ar)->der);

    (*ar)->dato = (*elim)->dato;
    (*ar)->tamDato = (*elim)->tamDato;
    free((*elim));
    *elim = NULL;
}
