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
                     FILE *JugadoresDat, FILE *archIndices, SOCKET sockCliente)
{
    char *petOperacion, *petDatos;
    char peticion[BUFFER_SIZE];
    tArbol *indiceJugador;
    tJugadorDat datosJugador;
    tIndice jugadorOffset;

    if (sacarCola(colaPeticiones, peticion, BUFFER_SIZE) != TODO_OK)
    {
        sprintf(response, "ERROR, No se pudo procesar la peticion");
        send(sockCliente, response, strlen(response), 0);
        return ERROR_COLA;
    }

    petOperacion = strtok(peticion, ",");
    petDatos = strtok(NULL, "");

    int opcion = obtenerOpcion(petOperacion);
    switch (opcion)
    {
    case OP_BUSCAR:
        if ((indiceJugador = arbolBuscar(arbolIndice, petDatos, cmpIndices)))
        {
            // BUSCA EL INDICE DEL JUGADOR EN EL ARBOL PARA BUSCARLO EN JugadoresDat
            tIndice *indice = (tIndice *)((*indiceJugador)->dato);
            fseek(JugadoresDat, indice->offset, SEEK_SET);
            fread(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
            sprintf(response, "OK,%s,%d,%d,%d", datosJugador.nombre, datosJugador.cantPartidas, datosJugador.puntos, datosJugador.cantMov);
        }
        else
        {
            strcpy(response, "ERROR,Usuario no encontrado");
        }
        break;
    case OP_ALTA:


        // COPIA EL INDICE Y LO INSERTA EN EL ARCHIVO ArchIndice
        fseek(JugadoresDat, 0, SEEK_END);
        jugadorOffset.offset = ftell(JugadoresDat);
        strcpy(jugadorOffset.nombre, petDatos);
        insertarArbolBinConR(arbolIndice, &jugadorOffset, sizeof(tIndice), cmpIndices);
        fwrite(&jugadorOffset, sizeof(tIndice), 1, archIndices);
        fflush(archIndices);
        // INSERTA EN EL ARCHIVO JugadoresDat
        strcpy(datosJugador.nombre, petDatos);
        datosJugador.cantMov = 0;
        datosJugador.cantPartidas = 0;
        datosJugador.puntos = 0;
        fwrite(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
        sprintf(response, "OK,%s,%d,%d,%d", datosJugador.nombre, datosJugador.cantPartidas, datosJugador.puntos, datosJugador.cantMov);
        break;

    case OP_GUARDAR:
        trozarDatosJugador(petDatos,&datosJugador);
        strcpy(jugadorOffset.nombre, datosJugador.nombre); // guardamos el nombre del jugador en buscarJugador.nombre

        if ((indiceJugador = arbolBuscar(arbolIndice, &jugadorOffset, cmpIndices)))
        {
            // PREPARA LA VARIABLE CON LOS DATOS ACTUALIZADOS PARA SOBREESCRIBIRLOS EN JugadoresDat
            tIndice *indice = (tIndice *)((*indiceJugador)->dato);
            fseek(JugadoresDat, indice->offset, SEEK_SET);
            fwrite(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
            strcpy(response, "OK,Progreso guardado");
        }
        else
        {
            strcpy(response, "ERROR, No se pudo guardar el progreso");
        }
        break;

    case OP_HISTORIAL:
        rewind(JugadoresDat);
        fread(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
        while(!feof(JugadoresDat))
        {
            sprintf(response, "SIGUE,%s,%d,%d,%d", datosJugador.nombre, datosJugador.cantPartidas, datosJugador.puntos, datosJugador.cantMov);
            send(sockCliente, response, strlen(response), 0);
            Sleep(15);//genera una pausa de 10ms, esto le da tiempo al cliente para recibir las respuestas.
            fread(&datosJugador, sizeof(tJugadorDat), 1, JugadoresDat);
        }
        strcpy(response,"FIN,Fin de la lista de jugadores");
        break;
    }

    send(sockCliente, response, strlen(response), 0);
    fflush(JugadoresDat);

    return TODO_OK;
}

int obtenerOpcion(const char *operacion)
{
    if (strcmp(operacion, "ALTA") == 0)
        return OP_ALTA;

    if (strcmp(operacion, "BUSCAR") == 0)
        return OP_BUSCAR;

    if (strcmp(operacion, "GUARDAR") == 0)
        return OP_GUARDAR;

    if (strcmp(operacion, "VER_HISTORIAL") == 0)
        return OP_HISTORIAL;

    return 0;
}

void mostrarArchivo(FILE *fp)
{
    tJugadorDat jug;
    while (fread(&jug, sizeof(tJugadorDat), 1, fp))
    {
        printf("Nombre: %s\tPuntaje: %d\tCantidad de Movimientos: %d\tCantidad de partidas: %d\n",
               jug.nombre, jug.puntos, jug.cantMov, jug.cantPartidas);
    }
    fflush(fp);
}

void trozarDatosJugador(char *linea, tJugadorDat *dest)
{
    char *aux = strrchr(linea,',');
    if(aux)
    {
        dest->cantMov = atoi(aux+1);
        *aux = '\0';
    }

    aux = strrchr(linea,',');
    if(aux)
    {
        dest->puntos = atoi(aux+1);
        *aux = '\0';
    }

    aux = strrchr(linea,',');
    if(aux)
    {
        dest->cantPartidas = atoi(aux+1);
        *aux = '\0';
    }

    strcpy(dest->nombre,linea);
}
