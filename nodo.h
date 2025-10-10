#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#define MIN(X, Y)((X) < (Y) ? (X) : (Y))

typedef struct sNodo{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

#endif // NODO_H_INCLUDED
