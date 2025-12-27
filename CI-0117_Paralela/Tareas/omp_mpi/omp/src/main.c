// Copyright [2025] <Camila Rodríguez>
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "fileControl.h" // NOLINT
#include "plate.h"        // NOLINT
#include "report.h"       // NOLINT

#define MAX_LINE 1024
#define MAX_PLACAS 100

char linea[MAX_LINE];
int iteracionesArray[MAX_PLACAS];
int contador = 0;

int main(int argc, char *argv[]) {
    clock_t inicio, fin;
    double tiempo_ejecucion;
    inicio = clock();

    limpiar_directorio("resultados");

    if (argc < 2) {
        printf("Uso: %s <archivo_trabajo> [num_threads]\n", argv[0]);
        return 1;
    }

    // Extraer el directorio del jobPath
    char *jobPath = argv[1];
    char *jobPathCopy = strdup(jobPath);
    char *jobDir = dirname(jobPathCopy);

    // Si no se pasa numThreads, usar la cantidad de núcleos disponibles
    int numThreads;
    if (argc >= 3) {
        numThreads = atoi(argv[2]);
    } else {
        // Obtener la cantidad de núcleos disponibles
        numThreads = omp_get_max_threads();
        printf("Usando cantidad de núcleos: %d\n", numThreads);
    }

    // Establecer el número de threads para OpenMP
    omp_set_num_threads(numThreads);

    printf("Intentando abrir: '%s'\n", jobPath);
    FILE *jobFile = fopen(jobPath, "r");

     // Verificar que se haya abierto correctamente
    if (!jobFile) {
        perror("Error al abrir el archivo");
        free(jobPathCopy);
        return 1;
    }

    printf("Archivo %s abierto correctamente.\n", jobPath);

    char lineas[MAX_PLACAS][MAX_LINE];
    int totalPlacas = 0;
    while (fgets(lineas[totalPlacas], MAX_LINE, jobFile)) {
        lineas[totalPlacas][strcspn(lineas[totalPlacas], "\n")] = '\0';
        totalPlacas++;
    }
    fclose(jobFile);  // Cerrar archivo

    // Paralelización con OpenMP
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < totalPlacas; i++) {
        int indice_local;

        // Sección crítica para incrementar el contador
        #pragma omp critical
        {
            indice_local = contador;
            contador++;
        }

        // Crear la estructura Plate y ejecutar la simulación
        crear_plate(lineas[i], iteracionesArray, &indice_local, jobDir);
    }

    crear_reporte(jobPath, iteracionesArray);

    fin = clock();  // Detener cronómetro
    tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo total de ejecución: %.6f segundos\n", tiempo_ejecucion);

    free(jobPathCopy);
    return 0;
}
