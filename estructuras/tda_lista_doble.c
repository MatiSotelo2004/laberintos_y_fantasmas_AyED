#include "tda_lista_doble.h"

void crearLista(tLista* lista){
    *lista=NULL;
}
int insertarListaDetras(tLista* lista,const void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    tNodoLista* auxAnt;
    tNodoLista* nue=(tNodoLista*)malloc(sizeof(tNodoLista));
    void* info=(void*)malloc(tam);
    if(!nue || !info){
        free(nue);
        free(info);
        return SIN_MEMORIA;
    }
    nue->info=info;
    memcpy(nue->info,dato,tam);
    nue->tam=tam;
    if(!actual){
        nue->sig=NULL;
        nue->ant=NULL;
        auxAnt=NULL;
    }else{
        auxAnt=actual->ant;
        nue->sig=actual;
        nue->ant=auxAnt;
        actual->ant=nue;
    }
    if(auxAnt){
        auxAnt->sig=nue;
    }
    *lista=nue;
    return TODO_OK;
}
int insertarListaDelante(tLista* lista,const void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    tNodoLista* auxSig;
    tNodoLista* nue=(tNodoLista*)malloc(sizeof(tNodoLista));
    void* info=(void*)malloc(tam);
    if(!nue || !info){
        free(nue);
        free(info);
        return SIN_MEMORIA;
    }
    nue->info=info;
    memcpy(nue->info,dato,tam);
    nue->tam=tam;
    if(!actual){
        nue->sig=NULL;
        nue->ant=NULL;
        auxSig=NULL;
    }else{
        auxSig=actual->sig;
        nue->sig=auxSig;
        nue->ant=actual;
        actual->sig=nue;
    }
    if(auxSig){
        auxSig->ant=nue;
    }
    *lista=nue;
    return TODO_OK;
}

int insertarOrdenadoLista(tLista* lista,const void* dato,unsigned tam,Cmp cmp,Duplicado condicion,Act act){
    tNodoLista* actual=*lista;
    tNodoLista* auxSig;
    tNodoLista* auxAnt;
    tNodoLista* nue;
    void* info;
    if(!actual){
        auxAnt=NULL;
        auxSig=NULL;
    }else{
        while(actual->sig && (cmp(dato,actual->info))>0){
            actual=actual->sig;
        }
        while(actual->ant && (cmp(dato,actual->info))<0){
            actual=actual->ant;
        }
        if((cmp(dato,actual->info))==0){
            if(condicion==SIN_DUPLICADO){
                if(act)
                    act((actual)->info,dato);
                return ES_DUPLICADO;
            }
        }
        if(cmp(dato,actual->info)>0){
            auxSig=actual->sig;
            auxAnt=actual;
        }else{
            auxAnt=actual->ant;
            auxSig=actual;
        }
    }
    nue=(tNodoLista*)malloc(sizeof(tNodoLista));
    info=(void*)malloc(tam);
    if(!nue || !info){
        free(info);
        free(nue);
        return SIN_MEMORIA;
    }
    nue->info=info;
    memcpy(nue->info,dato,tam);
    nue->tam=tam;
    nue->sig=auxSig;
    nue->ant=auxAnt;
    if(auxSig){
        auxSig->ant=nue;
    }
    if(auxAnt){
        auxAnt->sig=nue;
    }
    *lista=nue;
    return TODO_OK;
}
int sacarActualLista(tLista* lista,void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    tNodoLista* auxSig;
    tNodoLista* auxAnt;
    if(!actual){
        return LISTA_VACIA;
    }else{
        auxSig=actual->sig;
        auxAnt=actual->ant;
    }
    memcpy(dato,actual->info,MIN(actual->tam,tam));
    free(actual->info);
    free(actual);
    if(auxSig){
        auxSig->ant=auxAnt;
    }
    if(auxAnt){
        auxAnt->sig=auxSig;
    }
    if(auxSig){
        *lista=auxSig;
    }else{
        *lista=auxAnt;
    }
    return TODO_OK;
}

int sacarPorClaveOrdenadoLista(tLista* lista,void* dato,unsigned tam,Cmp cmp){
    tNodoLista* actual=*lista;
    tNodoLista* auxSig;
    tNodoLista* auxAnt;
    if(!actual){
        return LISTA_VACIA;
    }
    while(actual->sig && cmp(dato,actual->info)>0){
        actual=actual->sig;
    }
    while(actual->ant && cmp(dato,actual->info)<0){
        actual=actual->ant;
    }
    if(cmp(dato,actual->info)==0){
        auxAnt=actual->ant;
        auxSig=actual->sig;
    }else{
        return SIN_COINCIDENCIA;
    }
    if(auxSig){
        auxSig->ant=auxAnt;
    }
    if(auxAnt){
        auxAnt->sig=auxSig;
    }
    if(auxSig){
        *lista=auxSig;
    }else{
        *lista=auxAnt;
    }
    memcpy(dato,actual->info,MIN(tam,actual->tam));
    free(actual->info);
    free(actual);
    return TODO_OK;
}

int sacarPrimeroLista(tLista* lista,void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    tNodoLista* auxSig;
    if(!actual){
        return LISTA_VACIA;
    }
    while(actual->ant){
        actual=actual->ant;
    }
    memcpy(dato,actual->info,MIN(tam,actual->tam));
    auxSig=actual->sig;
    if(auxSig){
        auxSig->ant=actual->ant;
    }
    free(actual->info);
    free(actual);
    *lista=auxSig;
    return TODO_OK;
}
int sacarUltimoLista(tLista* lista,void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    tNodoLista* auxAnt;
    if(!actual){
        return LISTA_VACIA;
    }
    while(actual->sig){
        actual=actual->sig;
    }
    memcpy(dato,actual->info,MIN(actual->tam,tam));
    auxAnt=actual->ant;
    if(auxAnt){
        auxAnt->sig=actual->sig;
    }
    free(actual->info);
    free(actual);
    *lista=auxAnt;
    return TODO_OK;
}
void vaciarLista(tLista* lista){
    tNodoLista* elim;
    tNodoLista* auxSig;
    tNodoLista* auxAnt;
    while(*lista){
        elim=*lista;
        auxSig=elim->sig;
        auxAnt=elim->ant;
        if(auxAnt){
            auxAnt->sig=auxSig;
        }
        if(auxSig){
            auxSig->ant=auxAnt;
        }
        free(elim->info);
        free(elim);
        if(auxSig){
            *lista=auxSig;
        }else{
            *lista=auxAnt;
        }
    }
}
int listaLlena(const tLista* lista,unsigned tam){
    tNodoLista* nue=(tNodoLista*)malloc(sizeof(tNodoLista));
    void* info=(void*)malloc(tam);
    free(nue);
    free(info);
    return !nue || !info;
}
int listaVacia(const tLista* lista){
    return (*lista)==NULL;
}

void recorrerListaIzqDer(const tLista* lista, AccionLista accion){
    tNodoLista* actual=*lista;
    if(actual){
        while((actual)->ant){
            actual=(actual)->ant;
        }
    }
    while(actual){
        accion((actual)->info);
        actual=(actual)->sig;
    }
}

void recorrerListaDerIzq(const tLista* lista, AccionLista accion){
    tNodoLista* actual=*lista;
    if(actual){
        while((actual)->sig){
            actual=(actual)->sig;
        }
    }
    while(actual){
        accion((actual)->info);
        actual=(actual)->ant;
    }
}

int verActual(const tLista* lista,void* dato,unsigned tam){
    tNodoLista* actual=*lista;
    if(!actual){
        return LISTA_VACIA;
    }
    memcpy(dato,actual->info,MIN(tam,actual->tam));
    return TODO_OK;
}

int eliminarTodasLasCoincidenciasLista(tLista* lista,Filtro filtro){
    tNodoLista* actual = *lista;
    if(!actual){
        return LISTA_VACIA;
    }
    while(actual->ant){
        actual=actual->ant;
    }
    while(actual){
        if(filtro(actual->info)==0){
            sacarActualLista(&actual,actual->info,actual->tam);
        }else{
            *lista=actual;
            actual=actual->sig;
        }
    }
    return TODO_OK;
}

int buscarEnLista(const tLista* lista,void* dato,unsigned tam,Cmp cmp){
    tNodoLista* actual=*lista;
    if(!actual){
        return LISTA_VACIA;
    }
    while(actual->sig && cmp(dato,actual->info)>0){
        actual=actual->sig;
    }
    while(actual->ant && cmp(dato,actual->info)<0){
        actual=actual->ant;
    }
    if(cmp(dato,actual->info)!=0){
        return SIN_COINCIDENCIA;
    }
    memcpy(dato,actual->info,MIN(tam,actual->tam));
    return TODO_OK;
}
