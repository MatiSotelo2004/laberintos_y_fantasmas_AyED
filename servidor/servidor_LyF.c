#include "servidor_LyF.h"

int init_winsock()
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET crearServer()
{
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
        return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PUERTO);

    if (bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    if (listen(s, 1) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    return s;
}

int cargarIndices(tArbol *arbol, FILE *arch)
{
    tIndice nue;
    while (!feof(arch))
    {
        fread(&nue, sizeof(tIndice), 1, arch);
        if (insertarArbolBinConR(arbol, &nue, sizeof(nue), cmpIndices) != TODO_OK)
            return ERROR;
    }
    return TODO_OK;
}

int cmpIndices(const void *x, const void *y)
{
    const tIndice *str1 = (const tIndice *)x;
    const tIndice *str2 = (const tIndice *)y;

    return strcmp(str1->nombre, str2->nombre);
}

int procesarPeticion(tCola *colaPeticiones, tArbol *arbolIndice, char *response, 
    FILE *JugadoresDat, FILE *archIndices)
{
    char *petOperacion, *petDatos;
    char peticion[BUFFER_SIZE];
    tArbol *indiceJugador;
    tIndice jugadorAlta;

    tJugadorDat datosJugador;

    if (sacarCola(colaPeticiones, peticion, BUFFER_SIZE) != TODO_OK)
    {
        sprintf(response, "ERROR, No se pudo procesar la peticion");
        return ERROR_COLA;
    }

    petOperacion = strtok(peticion, ",");
    petDatos = strtok(NULL, "");
    puts(petOperacion);
    puts(petDatos);

    if (strcmp(petOperacion, OP_BUSCAR) == 0)
    {
        if ((indiceJugador = arbolBuscar(arbolIndice, petDatos, cmpIndices)))
        {
            tIndice *indice = (tIndice *)((*indiceJugador)->dato);
            fseek(JugadoresDat, indice->offset, SEEK_SET);
            fread(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
            sprintf(response, "OK,%s,%d,%d,%d", datosJugador.nombre, datosJugador.cantPartidas, datosJugador.puntos, datosJugador.cantMov);
        }
        else
        {
            sprintf(response, "ERROR,Usuario no encontrado");
        }
    }

    if (strcmp(petOperacion, OP_ALTA) == 0)
    {
        //COPIA EL INDICE Y LO INSERTA EN EL ARCHIVO ArchIndice
        fseek(JugadoresDat, 0, SEEK_END);
        jugadorAlta.offset = ftell(JugadoresDat);
        strcpy(jugadorAlta.nombre, petDatos);
        insertarArbolBinConR(arbolIndice, &jugadorAlta, sizeof(tIndice), cmpIndices);
        fwrite(&jugadorAlta, sizeof(tIndice), 1, archIndices);    
        fflush(archIndices);    
        //INSERTA EN EL ARCHIVO JugadoresDat
        strcpy(datosJugador.nombre, petDatos);
        datosJugador.cantMov = 0;
        datosJugador.cantPartidas = 0;
        datosJugador.puntos = 0;
        fwrite(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
        fflush(JugadoresDat);
        
        sprintf(response, "OK, Usuario dado de alta");
    }

    return TODO_OK;
}
