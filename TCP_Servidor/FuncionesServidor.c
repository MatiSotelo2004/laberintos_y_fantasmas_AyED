#include "FuncionesServidor.h"

void verHistorial(void *or, void *dst)
{
    FILE *fp = fopen((char*)or,"rb");

    if(!fp)
    {
        puts("No hay partidas registradas aun");
        return;
    }

    tHistorialJugador jug;
    fread(&jug,sizeof(tHistorialJugador),1,fp);

    while(!feof(fp))
    {
        printf("\nNombre: %-15s\n",jug.nombre);
        printf("Puntos: %-15d\n",jug.puntos);
        printf("Cantidad Movimientos: %-15d\n",jug.cantMov);
        fread(&jug,sizeof(tHistorialJugador),1,fp);
    }

    puts("");

    fclose(fp);
}

void archivoAgregarJugador(void *or, void *dest)
{
    tHistorialJugador *orig = (tHistorialJugador*)or;

    FILE *fp = fopen("jugadores.dat", "ab");
    if(!fp)
    {
        puts("Error al abrir el archivo\n");
        return ;
    }

    fwrite(orig,sizeof(tHistorialJugador),1,fp);
    fclose(fp);
}
