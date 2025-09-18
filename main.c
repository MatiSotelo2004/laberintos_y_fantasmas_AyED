//#include "tablero.h"
#include "tablero_v2.h"
//#include "objetos.h"
#include "menu.h"

void mostrarCharEnPantalla(void *fp, void *elem);

int main()
{

    /*
     *
     * PREGUNTAS
     1. La entrada puede ser de los laterales, o sólo del techo
     2. Preguntar por division de archivos .h y .c
     3. Cómo parsear el archivo de configs.txt (en qué forma vienen los datos)
     4. Es necesario validar los datos del archivo configs.txt // por ejemplo, el minimo tamaño de la matriz
     5.
     */
    srand(time(NULL));
    tConfigTablero config;
    tLaberinto tablero;
    //tPosObjeto objetos;


    cargarConfig(&config, "configs.txt");
    inicializarTablero(&tablero, &config);
    generarLab(&tablero);
    destruirTablero(&tablero);

    return 0;
}

void mostrarCharEnPantalla(void *fp, void *elem)
{
    fprintf((FILE*)fp,"%c",(*(char*)elem));
}
