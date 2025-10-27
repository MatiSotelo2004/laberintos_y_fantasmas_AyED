#include "menu.h"
#include "nuevaPartida.h"
int mostrarMenu(const char *opcionesValidas)
{
    char opcion;
    puts(TITULO);
    printOpciones();

    const char *pOpcionesValidasInicio = opcionesValidas;
    short esOpcionValida = 0;

    do
    {
        fflush(stdin);
        scanf("%c",&opcion);
        opcion = miToUpper(opcion);

        while(*opcionesValidas && !esOpcionValida)
        {
            if(*opcionesValidas == opcion)
                esOpcionValida = 1;

            opcionesValidas++;
        }

        opcionesValidas = pOpcionesValidasInicio;

    }while(!esOpcionValida);

    system("cls");
    return opcion;
}

void printOpciones()
{
    puts("--------------------------------");
    puts("[A] Ver ranking de jugadores.");
    puts("[B] Jugar nueva partida.");
    puts("[C] Salir del juego.");
    puts("--------------------------------");
    printf("Ingrese una opcion:");
}
