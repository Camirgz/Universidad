// Copyright [2025] <Camila Rodríguez>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // Incluir para medición de tiempo
#include "fileControl.h"  // NOLINT
#include "plate.h"    // NOLINT
#include "report.h"   // NOLINT

// Definir variables globales
#define MAX_LINE 1024
char linea[MAX_LINE];
int iteracionesArray[100];
int contador = 0;

int main(int argc, char *argv[]) {
    clock_t inicio, fin;          // Variables para medición de tiempo
    double tiempo_ejecucion;
    inicio = clock();             // Iniciar medición

    limpiar_directorio("resultados");   // Limpiar el directorio de resultados

    // Verificar que se haya pasado al menos un argumento
    if (argc < 2) {
        printf("Uso: %s <archivo_trabajo>\n", argv[0]);
        return 1;
    }

    // Obtener la ruta del archivo
    char *jobPath = argv[1];

    printf("Intentando abrir: '%s'\n", jobPath);
    FILE *jobFile = fopen(jobPath, "r");

    // Verificar que se haya abierto correctamente
    if (!jobFile) {
        perror("Error al abrir el archivo");
        return 1;
    }

    printf("Archivo %s abierto correctamente.\n", jobPath);

    // Leer cada línea del archivo
    while (fgets(linea, sizeof(linea), jobFile)) {
        crear_plate(linea, iteracionesArray, &contador);
    }

    fclose(jobFile);  // Cerrar archivo
    crear_reporte(jobPath, iteracionesArray);

    fin = clock();   // Finalizar medición
    tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC; // NOLINT
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo_ejecucion);

    return 0;
}
