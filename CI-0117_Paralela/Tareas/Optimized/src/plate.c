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

// Función que simula la difusión térmica en una placa, ahora esto es serial
int simular_difusion(double *temperaturas, uint64_t filas,
                                uint64_t columnas, const Plate *plate) {
    // Se reserva un buffer extra para almacenar la nueva temperatura
    double *buffer = (double *)malloc(filas * columnas * sizeof(double));
    if (!buffer) {
        printf("Error: No se pudo asignar memoria para el buffer.\n");
        return 0;
    }

    // 'src' apunta al arreglo con las temperaturas actuales
    // y 'dst' al buffer temporal.
    double *src = temperaturas;
    double *dst = buffer;
    int iteraciones = 0;
    double coef = plate->alpha * plate->delta_t / (plate->h * plate->h);
    double cambioMax;

    do {
        // Actualizar los boundaries en el buffer temporal
        copiar_boundaries(src, dst, filas, columnas);

        cambioMax = 0.0;
        // Se procesa únicamente el dominio interior
        for (uint64_t i = 1; i < filas - 1; i++) {
            for (uint64_t j = 1; j < columnas - 1; j++) {
                uint64_t idx = i * columnas + j;
                double arriba   = src[(i - 1) * columnas + j];
                double abajo    = src[(i + 1) * columnas + j];
                double izquierda = src[i * columnas + (j - 1)];
                double derecha   = src[i * columnas + (j + 1)];

                double nuevoValor = src[idx] +
                   coef * (arriba + abajo +
                    izquierda + derecha - 4.0 * src[idx]);
                dst[idx] = nuevoValor;

                double cambio = fabs(nuevoValor - src[idx]);
                if (cambio > cambioMax)
                    cambioMax = cambio;
            }
        }
        iteraciones++;

        // Se intercambian los punteros sin copiar la matriz entera, eficiencia
        double *temp = src;
        src = dst;
        dst = temp;
    } while (cambioMax > plate->epsilon);

    // Al finalizar, si el resultado final quedó en el buffer temporal,
    // se copia de vuelta a la matriz original.
    if (src != temperaturas) {
        memcpy(temperaturas, src, filas * columnas * sizeof(double));
    }
    free(buffer);

    printf("Difusión optimizada serial completada en %d iteraciones.\n",
         iteraciones);
    return iteraciones;
}

// Función para leer el plate desde un archivo binario
void leer_plate(const char *nombreBin, const Plate *plate,
                int *iteracionesArray, int *contador) {
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
         filas, columnas, plate);
    iteracionesArray[(*contador)] = iteraciones;
    (*contador)++;

    escribir_resultado(nombreBin, temperaturas, filas, columnas, iteraciones);
    free(temperaturas);
}

// Función para crear la estructura Plate a partir de una línea de texto
void crear_plate(const char *linea, int *iteracionesArray,
    int *contador, const char *jobDir) {

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
    leer_plate(rutaCompleta, &plate, iteracionesArray, contador);
    printf("%s procesado con éxito.\n", plate.archivo_lamina);
}
