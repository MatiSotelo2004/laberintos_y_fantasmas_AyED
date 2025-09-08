#include "menu.h"
int mostrarMenu()
{
    char opcion=1;
    while(miToUpper(opcion)!=OPCION_C)
    {
        printf("%s\n",TITULO);
        printOpciones();
        fflush(stdin);
        scanf("%c",&opcion);
        switch(miToUpper(opcion))
        {
        case OPCION_A:
            puts("La opcion de ver el ranking no esta implementada aun.");
            break;
        case OPCION_B:
            opcion=OPCION_C;
            break;
        case OPCION_C:
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
