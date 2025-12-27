// Copyright [2025] <Camila Rodríguez>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <pthread.h>
#include "plate.h"  //NOLINT
#include "fileControl.h"
typedef struct {
    double *temperaturas;
    double *nueva_temp;
    uint64_t filas;
    uint64_t columnas;
    double coef;
    double epsilon;
    uint64_t inicio;  // Primera fila
    uint64_t fin;  // Última fila
    double cambioMax_local;
} DatosHilo;

// Función para copiar las condiciones de frontera
void copiar_boundaries(double *temperaturas, double *nueva_temp,
    uint64_t filas, uint64_t columnas) {
    // Copiar filas de arriba y abajo para los límites
    for (size_t j = 0; j < columnas; j++) {
        nueva_temp[0 * columnas + j] = temperaturas[0 * columnas + j];
        nueva_temp[(filas - 1) * columnas + j] =
        temperaturas[(filas - 1) * columnas + j];
    }

    // Copiar columnas de izquierda y derecha para los límites
    for (size_t i = 1; i < filas - 1; i++) {
        nueva_temp[i * columnas + 0] = temperaturas[i * columnas + 0];
        nueva_temp[i * columnas + (columnas - 1)]
        = temperaturas[i * columnas + (columnas - 1)];
    }
}

// Función que calcula la difusión térmica en una sección
void* calcular_difusion(void *arg) {
    // Parsear los argumentos
    DatosHilo *datos = (DatosHilo*) arg;  //NOLINT
    double cambioMax_local = 0.0;

    // Calcular la difusión térmica para la sección asignada
    for (uint64_t i = datos->inicio; i < datos->fin; i++) {
        for (uint64_t j = 1; j < datos->columnas - 1; j++) {
            uint64_t idx = i * datos->columnas + j;

            double arriba = datos->temperaturas[(i - 1) * datos->columnas + j];
            double abajo = datos->temperaturas[(i + 1) * datos->columnas + j];

            double izquierda =
            datos->temperaturas[i * datos->columnas + (j - 1)];

            double derecha =
            datos->temperaturas[i * datos->columnas + (j + 1)];

            datos->nueva_temp[idx] = datos->temperaturas[idx] + datos->coef *
                                     (arriba + abajo + izquierda + derecha -
                                        4.0 * datos->temperaturas[idx]);

            double cambio =
            fabs(datos->nueva_temp[idx] - datos->temperaturas[idx]);

            if (cambio > cambioMax_local)
                cambioMax_local = cambio;
        }
    }
    datos->cambioMax_local = cambioMax_local;
    pthread_exit(NULL);  // Termina el hilo
}

// Función que simula la difusión térmica en una placa
int simular_difusion(double *temperaturas, uint64_t filas,
                     uint64_t columnas, const Plate *plate, int numThreads) {
    printf("Iniciando simulación de difusión con %d hilos\n", numThreads);

    double *nueva_temp = (double *)malloc(filas * columnas * sizeof(double));  //NOLINT
    if (!nueva_temp) {
        printf("Error: No se pudo asignar memoria para la matriz temporal.\n");
        return 0;
    }

    int iteraciones = 0;
    double cambioMax;
    double coef = plate->alpha * plate->delta_t / (plate->h * plate->h);
    if (coef > 0.25) {
        printf("Coeficiente (%.6lf) puede causar inestabilidad.\n", coef);
    }


    do {
        copiar_boundaries(temperaturas, nueva_temp, filas, columnas);

        pthread_t *hilos = malloc(numThreads * sizeof(pthread_t));
        if (hilos == NULL) {
            fprintf(stderr, "No se pudo asignar memoria para los hilos.\n");
            free(nueva_temp);
            return 0;
        }
        DatosHilo *datos = malloc(numThreads * sizeof(DatosHilo));
        if (datos == NULL) {
            fprintf(stderr, "No se pudo asignar memoria para los hilos.\n");
            free(hilos);
            free(nueva_temp);
            return 0;
        }

        // Dividir el trabajo entre los hilos
        uint64_t interiorRows = filas - 2;
        uint64_t rowsPerThread = interiorRows / numThreads;
        uint64_t extra = interiorRows % numThreads;
        uint64_t current = 1;  // La primera fila interna

        // Asignar el rango de filas a cada hilo
        for (int i = 0; i < numThreads; i++) {
            datos[i].temperaturas = temperaturas;
            datos[i].nueva_temp = nueva_temp;
            datos[i].filas = filas;
            datos[i].columnas = columnas;
            datos[i].coef = coef;
            datos[i].epsilon = plate->epsilon;
            datos[i].inicio = current;
            uint64_t asignar = rowsPerThread;
            if (extra > 0) {
                asignar++;
                extra--;
            }
            datos[i].fin = current + asignar;
            datos[i].cambioMax_local = 0.0;
            current = datos[i].fin;
        }

        // Crear los hilos
        for (int i = 0; i < numThreads; i++) {
            int rc =
            pthread_create(&hilos[i], NULL, calcular_difusion, &datos[i]);

            if (rc != 0) {
                fprintf(stderr, "Error al crear el hilo %d\n", i);

                // Limpiar memoria en caso de error
                free(hilos);
                free(datos);
                free(nueva_temp);
                return 0;
            }
        }

        // Esperar a que todos los hilos terminen y recopilar el máximo cambio
        cambioMax = 0.0;
        for (int i = 0; i < numThreads; i++) {
            int rc = pthread_join(hilos[i], NULL);
            if (rc != 0) {
                fprintf(stderr, "Error al esperar el hilo %d\n", i);
            }
            if (datos[i].cambioMax_local > cambioMax) {
                cambioMax = datos[i].cambioMax_local;
            }
        }

        // Liberar memoria de los hilos
        free(hilos);
        free(datos);

        // Actualizar la matriz de temperaturas
        memcpy(temperaturas, nueva_temp, filas * columnas * sizeof(double));
        iteraciones++;
    } while (cambioMax > plate->epsilon);

    printf("Difusión completada en %d iteraciones.\n", iteraciones);
    free(nueva_temp);
    return iteraciones;
}

// Función para leer el plate desde un archivo binario
void leer_plate(const char *nombreBin, const Plate *plate,
                int *iteracionesArray, int *contador, int numThreads) {
    FILE *bin = fopen(nombreBin, "rb");
    if (!bin) {
        perror("Error al abrir el archivo binario");
        return;
    }

    // Cambiar de sizeof(double) a sizeof(int)
    uint64_t filas, columnas;
    if (fread(&filas, sizeof(u_int64_t), 1, bin) != 1 ||
        fread(&columnas, sizeof(u_int64_t), 1, bin) != 1) {
        printf("Error: No se pudieron leer las dimensiones.\n");
        fclose(bin);
        return;
    }

    if (filas == 0 || columnas == 0) {
        printf("Error: Dimensiones inválidas, (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas); //NOLINT
        fclose(bin);
        return;
    }

    double *temperaturas = (double *)malloc(filas * columnas * sizeof(uint64_t));  //NOLINT
    if (!temperaturas) {
        printf("Error: No se pudo asignar memoria para la matriz.\n");
        fclose(bin);
        return;
    }

    if (fread(temperaturas, sizeof(double),
    (size_t)(filas * columnas), bin) != (size_t)(filas * columnas)) {  //NOLINT
        printf("Error: No se pudieron leer los datos de temperatura.\n");
        free(temperaturas);
        fclose(bin);
        return;
    }

    fclose(bin);
    printf("Lectura exitosa del archivo binario (%" PRIu64 "x%" PRIu64 ").\n", filas, columnas); //NOLINT

    // Ejecutar la simulación concurrente, pasando el número de hilos a usar.
    int iteraciones = simular_difusion(temperaturas,
         filas, columnas, plate, numThreads);
    iteracionesArray[(*contador)] = iteraciones;
    (*contador)++;

    escribir_resultado(nombreBin, temperaturas, filas, columnas, iteraciones);
    free(temperaturas);
}

// Función para crear la estructura Plate a partir de una línea de texto
void crear_plate(const char *linea, int *iteracionesArray,
    int *contador, int numThreads, const char *jobDir) {

    Plate plate;

    if (sscanf(linea, "%255s %lf %lf %lf %lf", plate.archivo_lamina,
               &plate.delta_t, &plate.alpha, &plate.h, &plate.epsilon) != 5) {
        printf("Advertencia: Línea ignorada -> %s\n", linea);
        return;
    }

    char rutaCompleta[512];
    snprintf(rutaCompleta, sizeof(rutaCompleta),
    "%s/%s", jobDir, plate.archivo_lamina);  // Corregido aquí

    printf("\nCargando archivo binario: %s\n", rutaCompleta);
    leer_plate(rutaCompleta, &plate, iteracionesArray, contador, numThreads);
    printf("%s procesado con éxito.\n", plate.archivo_lamina);
}
