#include <stdio.h>
#include "servidor_LyF.h"

int main()
{
    tCola colaPeticiones;
    tArbol arbolIndice;
    FILE *jugadoresDat, *indiceDat;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int bytesRecividos;

    SOCKET client_socket, server_socket;
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);

    // CREA LA COLA PARA LAS PETICIONES
    crearCola(&colaPeticiones);

    // SE ABRE EL ARCHIVO DE INDICES
    indiceDat = fopen("Indice.dat", "a+b");
    // CREA EL ARBOL Y CARGA LOS INDICES
    cargarIndices(&arbolIndice, indiceDat);

    // SE ABRE EL ARCHIVO CON LOS DATOS DE LOS JUGADORES
    jugadoresDat = fopen("Jugadores.dat", "a+b");

    if (init_winsock() != 0)
    {
        printf("Error al inicializar Winsock\n");
        return -1;
    }

    // CREA EL SERVER Y ESCUCHA EL PUERTO 12345
    server_socket = crearServer();
    if (server_socket == INVALID_SOCKET)
    {
        printf("Error al crear socket del servidor\n");
        WSACleanup();
        return 1;
    }
    printf("Servidor escuchando en puerto %d...\n", PUERTO);

    // SE CONECTA CON EL CLIENTE
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_socket == INVALID_SOCKET)
    {
        printf("Error en accept()\n");
        closesocket(server_socket);
        WSACleanup();
        fclose(jugadoresDat);
        fclose(indiceDat);
        return 1;
    }
    printf("Cliente conectado.\n");

    while ((bytesRecividos = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0)
    {
        buffer[bytesRecividos] = '\0';
        printf("Recibido: %s\n", buffer);

        //ENCOLA LAS PETICIONES
        if (ponerCola(&colaPeticiones, buffer, BUFFER_SIZE) != TODO_OK)
            printf("Cola de peticiones llena\n");

        //PROCESA LA PETICION Y DEVUELVE EL RESULTADO POR 'RESPONSE'
        procesarPeticion(&colaPeticiones,&arbolIndice, response, jugadoresDat, indiceDat);

        send(client_socket, response, strlen(response), 0);
        printf("Enviado:  %s\n", response);
    }

    // CIERRA LAS CONEXIONES
    printf("Conexion cerrada.\n");
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    fclose(jugadoresDat);
    fclose(indiceDat);
    return 0;
}
