#include "tcp_servidor.h"

int inicializarWinsock()
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET crearSocketServer()
{
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

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

int servidorResponderCliente(SOCKET socketServidor, Accion funcion)
{
    struct sockaddr_in direccionCliente;
    int tamDireccionCliente = sizeof(direccionCliente);

    SOCKET socketCliente = accept(socketServidor, (struct sockaddr *)&direccionCliente, &tamDireccionCliente);
    if (socketCliente == INVALID_SOCKET)
    {
        printf("Error en accept()\n");
        return -1;
    }

    printf("Cliente conectado.\n");

    int tamEnviadoPorClienteParaRecibirInfo; //es el tamaño necesario para guardar la informacion que envia el cliente

    if(recv(socketCliente,(char*)&tamEnviadoPorClienteParaRecibirInfo,sizeof(int),0) <= 0)
    {
        puts("No se recibio un tamaño valido de informacion");
        return -1;
    }

    void *recibido = malloc(tamEnviadoPorClienteParaRecibirInfo);
    if(!recibido)
    {
        closesocket(socketCliente);
        return SIN_MEMORIA_SERVIDOR;
    }

    if(recv(socketCliente, recibido, tamEnviadoPorClienteParaRecibirInfo, 0) <= 0)
    {
        puts("Error al recibir la informacion");
        return -1;
    }

    int tamEnviadoPorClientaParaRespuesta;

    if(recv(socketCliente,(char*)&tamEnviadoPorClientaParaRespuesta,sizeof(int),0) <= 0)
    {
        puts("No se recibio un tamaño valido de informacion");
        return -1;
    }

    void *respuesta = malloc(tamEnviadoPorClientaParaRespuesta);
    if(!respuesta)
    {
        closesocket(socketCliente);
        return SIN_MEMORIA_SERVIDOR;
    }

    funcion(recibido,respuesta);
    if(send(socketCliente,(const char*)&respuesta, tamEnviadoPorClientaParaRespuesta, 0) <= 0)
    {
        puts("Error enviando datos a cliente");
        return ERROR;
    }

    printf("Conexion cerrada.\n");
    closesocket(socketCliente);
    free(recibido);
    getchar();
    return TODO_OK;
}

