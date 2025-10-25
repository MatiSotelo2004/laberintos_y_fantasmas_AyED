#include "HistorialPartidas.h"

int servidorBuscarNombre(SOCKET *sock, const char *nombre, tJugadorDat *destino)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "BUSCAR,%s", nombre);

    if (send(*sock, buffer, strlen(buffer), 0) < 0)
    {
        puts("Error al enviar informacion al servidor");
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
    if (strcmp(respuestaServer, "ERROR") == 0)
        return NO_EXISTE;

    char *datos = strtok(NULL, "");
    sscanf(datos, FORMATO_ENVIAR_DATOS_JUGADOR, destino->nombre, &destino->cantPartidas, &destino->puntos, &destino->cantMov);

    return EXISTE;
}

int servidorDarAltaJugador(SOCKET *sock, const char *nombre, tJugadorDat *destino)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "ALTA,%s", nombre);

    if (send(*sock, buffer, strlen(buffer), 0) < 0)
    {
        puts("Error al enviar informacion al servidor");
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
    if (strcmp(respuestaServer, "ERROR") == 0)
    {
        puts("Error al crear el jugador");
        return NO_EXISTE;
    }

    puts("Jugador creado con exito");
    char *datos = strtok(NULL, "");
    sscanf(datos, FORMATO_ENVIAR_DATOS_JUGADOR, destino->nombre, &destino->cantPartidas, &destino->puntos, &destino->cantMov);

    return EXISTE;
}

int servidorCargarNuevaPartida(SOCKET *sock, const tJugadorDat *jugador)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer,"GUARDAR,%s,%d,%d,%d",jugador->nombre,jugador->cantPartidas + 1,jugador->puntos,jugador->cantMov);
    if (send(*sock,buffer,strlen(buffer),0) <= 0)
    {
        puts("Error al enviar datos al servidor");
        return SERVIDOR_ERROR;
    }

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
