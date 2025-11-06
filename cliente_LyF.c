#include "cliente_LyF.h"

int servidorBuscarNombre(SOCKET *sock, const char *nombre, tJugadorDat *destino)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "BUSCAR,%s", nombre);
    char respuesta[BUFFER_SIZE];
    char datosRespuesta[BUFFER_SIZE];
    if(servidorInteractuar(sock,buffer,respuesta,datosRespuesta) == SERVIDOR_ERROR)
        return SERVIDOR_ERROR;
    if(strcmp(respuesta,"ERROR")==0){
        return NO_EXISTE;
    }
    trozarDatosJugadorDat(datosRespuesta,destino);
    return EXISTE;
}

int servidorDarAltaJugador(SOCKET *sock, const char *nombre, tJugadorDat *destino)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "ALTA,%s", nombre);
    char respuesta[BUFFER_SIZE];
    char datosRespuesta[BUFFER_SIZE];
    if(servidorInteractuar(sock,buffer,respuesta,datosRespuesta) != TODO_OK)
    {
        puts("No se puede dar de alta el jugador nuevo.");
        return SERVIDOR_ERROR;
    }

    puts("Jugador creado con exito");
    trozarDatosJugadorDat(datosRespuesta,destino);
    return TODO_OK;
}

int servidorCargarNuevaPartida(SOCKET *sock, const tJugadorDat *jugador)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "GUARDAR,%s,%d,%d,%d", jugador->nombre, jugador->cantPartidas, jugador->puntos, jugador->cantMov);
    char respuesta[BUFFER_SIZE];
    char datosRespuesta[BUFFER_SIZE];
    if(servidorInteractuar(sock,buffer,respuesta,datosRespuesta) != TODO_OK)
    {
        puts("Error al enviar datos al servidor");
        return SERVIDOR_ERROR;
    }

    return TODO_OK;
}

int servidorInteractuar(SOCKET *sock, const char *peticion, char *estadoDevuelto, char *datosDevueltos)
{
    char buffer[BUFFER_SIZE];

    if (send(*sock, peticion, strlen(peticion), 0) <= 0)
    {
        puts("Error al enviar datos al servidor");
        return SERVIDOR_ERROR;
    }

    int bytesRecibidos = recv(*sock, buffer, BUFFER_SIZE - 1, 0);

    if (bytesRecibidos <= 0)
    {
        puts("Error al recibir informacion del servidor");
        return SERVIDOR_ERROR;
    }

    buffer[bytesRecibidos] = '\0';
    char *respuestaServer = strtok(buffer, ",");
    char *petDatos  = strtok(NULL, "");
    strcpy(estadoDevuelto,respuestaServer);
    strcpy(datosDevueltos,petDatos);
    return TODO_OK;
}

int servidorVerHistorialPartidas(SOCKET *sock)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "VER_HISTORIAL,");
    if (send(*sock, buffer, strlen(buffer), 0) <= 0)
    {
        puts("Error al enviar datos al servidor");
        return SERVIDOR_ERROR;
    }

    int bytesRecibidos = recv(*sock, buffer, BUFFER_SIZE - 1, 0);

    if (bytesRecibidos <= 0)
    {
        puts("Error al recibir informacion del servidor");
        return SERVIDOR_ERROR;
    }

    buffer[bytesRecibidos] = '\0';
    char *respuestaServer = strtok(buffer, ",");
    char *datos = strtok(NULL, "");
    tJugadorDat jug;

    while(strcmp(respuestaServer, "SIGUE") == 0)
    {
        trozarDatosJugadorDat(datos,&jug);
        printf("Nombre: %s\nPuntaje: %d\nCantidad de Partidas: %d\nCantidad de movimientos: %d\n\n",
               jug.nombre,jug.puntos,jug.cantPartidas,jug.cantMov);

        bytesRecibidos = recv(*sock, buffer, BUFFER_SIZE - 1, 0);
         if (bytesRecibidos <= 0)
        {
            puts("Error al recibir informacion del servidor");
            return SERVIDOR_ERROR;
        }
        buffer[bytesRecibidos] = '\0';
        respuestaServer = strtok(buffer, ",");
        datos = strtok(NULL, "");
    }

    system("pause");
    system("cls");
    return TODO_OK;
}

int inicializarWinsock(void)
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET conectarServer(const char *server_ip, int port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        closesocket(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

int iniciarServidor(SOCKET *sockCliente)
{
    system("start \"Server\" \"servidor\\bin\\Debug\\servidor.exe\"");
    if (inicializarWinsock() != 0)
    {
        printf("Error al inicializar Winsock\n");
        return SERVIDOR_OFF;
    }

    *sockCliente = conectarServer(SERVER_IP, PORT);
    if (*sockCliente == INVALID_SOCKET)
    {
        printf("No se pudo conectar al servidor\n");
        WSACleanup();
        return SERVIDOR_OFF;
    }

    printf("Conectado al servidor.\n");
    return SERVIDOR_ON;
}

void trozarDatosJugadorDat(char *linea, tJugadorDat *dest)
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
