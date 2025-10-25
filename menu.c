#include "menu.h"
int mostrarMenu()
{
    char opcion=1;
    while(miToUpper(opcion)!=OPCION_SALIR)
    {
        printf("%s\n",TITULO);
        printOpciones();
        fflush(stdin);
        scanf("%c",&opcion);
        switch(miToUpper(opcion))
        {
            case OPCION_VER_HISTORIAL:
                //verPartidas("jugadores.dat");
                //void *aux = servidorInteractuar(sizeof(NOMBRE_ARCHIVO_HISTORIAL),1,LLAMADA_A_SERVIDOR_VER_HISTORIAL,NULL,copiarNombreArchivo);
                //la variable aux la uso porque esa funcion devuelve la respuesta que me dió el servidor, pero como no la necesito, la libero
                //free(aux);
                break;
            case OPCION_NUEVA_PARTIDA:
                opcion=OPCION_SALIR;
                break;
            case OPCION_SALIR:
                puts("Gracias por jugar!!!");
                puts("Saliendo...");
                return FIN_JUEGO;
                break;
            default:
                puts("Opcion incorrecta, por favor ingrese nuevamente.");
            break;
        }
        system("pause");
        system("cls");
    }
    return TODO_OK;
}

void printOpciones()
{
    puts("--------------------------------");
    puts("[A] Ver ranking de jugadores.");
    puts("[B] Jugar nueva partida.");
    puts("[C] Salir del juego.");
    puts("--------------------------------");
    puts("Ingrese una opcion:");
}
