#include "servidor_LyF.h"

int init_winsock()
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET crearServer()
{
    SOCKET s;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PUERTO);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
        return INVALID_SOCKET;
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
        if (insertarArbolBin(arbol, &nue, sizeof(nue), cmpIndices) != TODO_OK)
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

int procesarPeticion(tCola *colaPeticiones, tArbol arbolIndice, char *response, FILE *JugadoresDat)
{
    char *petOperacion, *petDatos;
    char peticion[BUFFER_SIZE];
    unsigned offsetIndice;
    tJugadorDat datosJugador;

    if (descolarCola(colaPeticiones, peticion, BUFFER_SIZE) != TODO_OK)
        return ERROR;

    petOperacion = strtok(peticion, ",");
    petDatos = strtok(NULL, "");

    if (strcmp(petOperacion, "BUSCAR") == 0)
    {
        if (buscarIndice(arbolIndice, petDatos, &offsetIndice) == EXISTE)
        {
            fseek(JugadoresDat, offsetIndice, SEEK_SET);
            fread(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
            sprintf(response, "OK, %s,%d,%d,%d", datosJugador.nombre, datosJugador.cantPartidas, datosJugador.puntos, datosJugador.cantMov);
        }
        else
        {
            sprintf(response, "ERROR,Usuario no encontrado");
        }
    }
}