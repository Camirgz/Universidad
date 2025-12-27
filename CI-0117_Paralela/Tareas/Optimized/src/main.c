// Copyright [2025] <Camila Rodríguez>
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "fileControl.h" // NOLINT
#include "plate.h"        // NOLINT
#include "report.h"       // NOLINT

#define MAX_LINE 1024
#define MAX_PLACAS 100

char linea[MAX_LINE];
int iteracionesArray[MAX_PLACAS];
int contador = 0;


// Estructura para pasar argumentos a los hilos
// Se utiliza para evitar el uso de variables globales
typedef struct {
    char linea[MAX_LINE];
    int *iteracionesArray;
    int *contador;
    int numThreads;
    const char *jobDir;
    pthread_mutex_t *mutex;
} ArgsSimulacion;

// Función que se ejecuta en cada hilo
// Se encarga de crear la estructura Plate y ejecutar la simulación
void* hilo_simulacion(void* arg) {
    ArgsSimulacion *args = (ArgsSimulacion*) arg;  // Parsear los argumentos

    // Mutex para asegurar que solo un hilo acceda al contador
    pthread_mutex_lock(args->mutex);
    int indice = *(args->contador);
    *(args->contador) += 1;
    pthread_mutex_unlock(args->mutex);

    // Crear la estructura Plate a partir de la línea de texto
    crear_plate(args->linea, args->iteracionesArray, &indice, args->jobDir);
    return NULL;
}

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
        numThreads = sysconf(_SC_NPROCESSORS_ONLN);
        printf("Usando cantidad de núcleos: %d\n", numThreads);
    }

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

    pthread_t hilos[MAX_PLACAS];
    ArgsSimulacion args[MAX_PLACAS];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < totalPlacas; i++) {
        strncpy(args[i].linea, lineas[i], MAX_LINE);
        args[i].iteracionesArray = iteracionesArray;
        args[i].contador = &contador;
        args[i].numThreads = numThreads;
        args[i].jobDir = jobDir;
        args[i].mutex = &mutex;

        pthread_create(&hilos[i], NULL, hilo_simulacion, &args[i]);
    }

    for (int i = 0; i < totalPlacas; i++) {
        pthread_join(hilos[i], NULL);
    }

    crear_reporte(jobPath, iteracionesArray);

    fin = clock();  // Detener cronómetro
    tiempo_ejecucion = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo total de ejecución: %.6f segundos\n", tiempo_ejecucion);

    free(jobPathCopy);
    return 0;
}
