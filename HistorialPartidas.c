#include "HistorialPartidas.h"

void* servidorInteractuar(unsigned tamElemEnviar, unsigned tamElemRespuesta, const char *ejecutarLlamadaAlServidor, void *extra, Accion filtroSobreDatoAEnviar)
{
    system(ejecutarLlamadaAlServidor);
    if (inicializarWinsock() != 0)
    {
        printf("Error al inicializar Winsock\n");
        return NULL;
    }

    SOCKET sock = conectarServer(SERVER_IP, PORT);
    if (sock == INVALID_SOCKET)
    {
        printf("No se pudo conectar al servidor\n");
        WSACleanup();
        return NULL;
    }

    printf("Conectado al servidor.\n");

    void *enviar = malloc(tamElemEnviar);
    if(!enviar)
    {
        puts("Sin memoria suficiente!");
        return NULL;
    }

    void *respuesta = malloc(tamElemRespuesta);
    if(!respuesta)
    {
        free(enviar);
        puts("Sin memoria suficiente!");
        return NULL;
    }

    if(filtroSobreDatoAEnviar)
        filtroSobreDatoAEnviar(enviar,extra);

    if (send(sock, (const char*)&tamElemEnviar, sizeof(int),0) < 0)
    {
        free(enviar);
        free(respuesta);
        printf("Error al enviar tamaño datos\n");
        closesocket(sock);
        return NULL;
    }

    if (send(sock, (const char*)enviar, tamElemEnviar,0) < 0)
    {
        free(enviar);
        free(respuesta);
        printf("Error al enviar datos\n");
        closesocket(sock);
        return NULL;
    }

    if (send(sock, (const char*)&tamElemRespuesta, sizeof(int),0) < 0)
    {
        free(enviar);
        free(respuesta);
        printf("Error al enviar datos\n");
        closesocket(sock);
        return NULL;
    }

    if(recv(sock,(char*)respuesta,tamElemRespuesta,0) < 0)
    {
        free(enviar);
        free(respuesta);
        puts("Ocurrio un error recibiendo respuesta del servidor");
        return NULL;
    }

    free(enviar);
    return respuesta;
}


int inicializarWinsock(void)
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET conectarServer(const char *server_ip, int port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        closesocket(sock);
        return INVALID_SOCKET;
    }

    return sock;
}
